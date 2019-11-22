using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetScriptFramework.Tools
{
    #region Block class

    /// <summary>
    /// Contains information about one block in a message.
    /// </summary>
    internal sealed class Block
    {
        #region Constructors

        /// <summary>
        /// Create a new block.
        /// </summary>
        /// <param name="message">Message where this block belongs in.</param>
        internal Block(Message message)
        {
            this.Message = message;
        }

        /// <summary>
        /// Copy a block to new message.
        /// </summary>
        /// <param name="block">Block to copy from.</param>
        /// <param name="msg">New message.</param>
        internal Block(Block block, Message msg)
        {
            this.Message = msg;
            this.Elements = block.Elements;
        }

        #endregion

        #region Block members

        /// <summary>
        /// Check if this block or any sub block has element with this type.
        /// </summary>
        /// <param name="type">Type to check.</param>
        /// <returns></returns>
        internal bool HasAnyElementType(BlockElementTypes type)
        {
            foreach (var x in this.Elements)
            {
                if (x.Key == type)
                    return true;

                if (x.Key == BlockElementTypes.Block && ((Block)x.Value).HasAnyElementType(type))
                    return true;
            }

            return false;
        }

        /// <summary>
        /// Parent message of block.
        /// </summary>
        private readonly Message Message;

        /// <summary>
        /// Elements of block.
        /// </summary>
        private readonly List<KeyValuePair<BlockElementTypes, object>> Elements = new List<KeyValuePair<BlockElementTypes, object>>();

        /// <summary>
        /// Convert block to string.
        /// </summary>
        /// <param name="parser">Parser to use.</param>
        /// <param name="result">Result is set here if we are successful. Otherwise error is set here.</param>
        /// <returns></returns>
        internal bool ToString(Parser parser, ref string result)
        {
            // Parse into this builder.
            StringBuilder str = new StringBuilder();

            // Function temporary data.
            string fn = null;
            List<string> args = null;

            // Start to parse.
            IArgument obj = parser["this"];
            for (int i = 0; i < this.Elements.Count; i++)
            {
                switch (this.Elements[i].Key)
                {
                    case BlockElementTypes.Argument:
                        obj = parser.ParseArgument(this.Message, (string)this.Elements[i].Value, obj);
                        if (obj == null)
                            obj = parser[(string)this.Elements[i].Value];
                        if (obj == null)
                        {
                            result = "Failed to parse argument \"" + this.Elements[i].Value + "\" on " + (obj != null ? obj.ToString() : "(null)") + "!";
                            return false;
                        }
                        break;

                    case BlockElementTypes.Variable:
                        {
                            string val = parser.ParseVariable(this.Message, (string)this.Elements[i].Value, obj);
                            if (val == null)
                            {
                                result = "Failed to parse variable \"" + this.Elements[i].Value + "\" on " + (obj != null ? obj.ToString() : "(null)") + "!";
                                return false;
                            }

                            str.Append(val);
                        }
                        break;

                    case BlockElementTypes.Literal:
                        if (fn != null)
                        {
                            if (args == null)
                                args = new List<string>() { (string)this.Elements[i].Value };
                            else
                                args[args.Count - 1] += (string)this.Elements[i].Value;
                        }
                        else
                            str.Append((string)this.Elements[i].Value);
                        break;

                    case BlockElementTypes.Block:
                        {
                            string val = null;
                            bool r = ((Block)this.Elements[i].Value).ToString(parser, ref val);
                            if (!r)
                            {
                                result = val;
                                return r;
                            }

                            if (fn != null)
                            {
                                if (args == null)
                                    args = new List<string>() { val };
                                else
                                    args[args.Count - 1] += val;
                            }
                            else
                                str.Append(val);
                        }
                        break;

                    case BlockElementTypes.Function:
                        {
                            if (fn != null)
                            {
                                result = "Found more than one function call in a block!";
                                return false;
                            }

                            fn = (string)this.Elements[i].Value;
                        }
                        break;

                    case BlockElementTypes.ParameterDelimiter:
                        {
                            if (fn == null)
                            {
                                result = "Found invalid parameter delimiter in a block!";
                                return false;
                            }

                            if (args == null)
                                args = new List<string>() { "" };
                            else
                                args.Add("");
                        }
                        break;

                    default:
                        throw new NotImplementedException();
                }
            }

            if (fn != null)
            {
                string val = parser.ParseFunction(this.Message, fn, args != null ? args.ToArray() : new string[0], obj);
                if (val == null)
                {
                    result = "Failed to parse function \"" + fn + "\" on " + (obj != null ? obj.ToString() : "(null)") + "!";
                    return false;
                }

                str.Append(val);
            }

            result = str.ToString();
            return true;
        }

        #endregion

        #region Static members

        /// <summary>
        /// Parse a block from text.
        /// </summary>
        /// <param name="message">Message where this block belongs in.</param>
        /// <param name="text">Text to parse from.</param>
        /// <param name="index">Current index in text.</param>
        /// <param name="result">Result will be set here if we return Ok.</param>
        /// <param name="isBlock">Is this a block or not.</param>
        /// <returns></returns>
        internal static string Parse(Message message, string text, ref int index, ref Block result, bool isBlock)
        {
            // Current token.
            StringBuilder str = new StringBuilder();

            // Current state of parse.
            BlockParseStates state = BlockParseStates.None;

            // Temporary variable.
            int len = 0;

            // Current block to return.
            Block block = new Block(message);

            // Parse until end.
            while (index < text.Length)
            {
                // If we have escaped then just append to token.
                if ((state & BlockParseStates.Escaped) != BlockParseStates.None)
                {
                    str.Append(text[index]);
                    state &= ~BlockParseStates.Escaped;
                    index++;
                    continue;
                }

                // Escape symbol.
                if (Parser.IsSymbol(text, index, ParserActions.Escape, ref len))
                {
                    state |= BlockParseStates.Escaped;
                    index += len;
                    continue;
                }

                // Literals are only allowed in block.
                if (isBlock)
                {
                    // End of literal.
                    if ((state & BlockParseStates.Literal) != BlockParseStates.None && Parser.IsSymbol(text, index, ParserActions.LiteralEnd, ref len))
                    {
                        // Advance index.
                        index += len;

                        // Remove literal state.
                        state &= ~BlockParseStates.Literal;
                        continue;
                    }

                    // Is literal.
                    if ((state & BlockParseStates.Literal) != BlockParseStates.None)
                    {
                        // Append to token.
                        str.Append(text[index]);
                        index++;
                        continue;
                    }

                    // Start of literal.
                    if (Parser.IsSymbol(text, index, ParserActions.LiteralStart, ref len))
                    {
                        // Advance index.
                        index += len;

                        // Add literal state.
                        state |= BlockParseStates.Literal;
                        continue;
                    }
                }

                // Ignore symbol.
                if ((isBlock && Parser.IsSymbol(text, index, ParserActions.BlockIgnore, ref len)) || Parser.IsSymbol(text, index, ParserActions.AlwaysIgnore, ref len))
                {
                    // Advance index.
                    index += len;

                    // Skip.
                    continue;
                }

                // End of block.
                if (isBlock && Parser.IsSymbol(text, index, ParserActions.VariableEnd, ref len))
                {
                    // Parameter list was not closed! Reached end of block unexpectedly.
                    if ((state & BlockParseStates.ParameterList) != BlockParseStates.None)
                        return "Reached end of block before closing parameter list at index " + index + " in string \"" + text + "\"!";

                    // Finish last token.
                    if (str.Length != 0)
                    {
                        // Somehow had tokens left after parameter list.
                        if ((state & BlockParseStates.HadParameterList) != BlockParseStates.None)
                            return "Reached end of block with invalid token at index " + index + " in string\"" + text + "\"!";

                        block.Elements.Add(new KeyValuePair<BlockElementTypes, object>(BlockElementTypes.Variable, str.ToString()));
                        str.Clear();
                    }

                    // Advance index.
                    index += len;

                    // Everything seems ok.
                    result = block;
                    return null;
                }

                // Start of block.
                if (Parser.IsSymbol(text, index, ParserActions.VariableStart, ref len))
                {
                    // Only in block.
                    if (isBlock)
                    {
                        // Sub-blocks are only allowed in parameters.
                        if ((state & BlockParseStates.ParameterList) == BlockParseStates.None)
                            return "Unexpected start of another block at index " + index + " in string \"" + text + "\"!";
                    }

                    // Finish last token.
                    if (str.Length != 0)
                    {
                        block.Elements.Add(new KeyValuePair<BlockElementTypes, object>(BlockElementTypes.Literal, str.ToString()));
                        str.Clear();
                    }

                    // Advance index.
                    index += len;

                    // Read another block recursively.
                    Block read = null;
                    string r = Block.Parse(message, text, ref index, ref read, true);

                    // Error occurred while reading sub-block. Return error.
                    if (r != null)
                        return r;

                    // Add block to elements of this block.
                    block.Elements.Add(new KeyValuePair<BlockElementTypes, object>(BlockElementTypes.Block, read));
                    continue;
                }

                // Block control symbols.
                if (isBlock)
                {
                    // Token delimiter.
                    if ((state & BlockParseStates.ParameterList) == BlockParseStates.None && Parser.IsSymbol(text, index, ParserActions.VariableDelimiter, ref len))
                    {
                        // Invalid location for delimiter.
                        if (str.Length == 0)
                            return "Unexpected argument delimiter at index " + index + " in string \"" + text + "\"!";

                        // Advance index.
                        index += len;

                        // Convert to argument.
                        block.Elements.Add(new KeyValuePair<BlockElementTypes, object>(BlockElementTypes.Argument, str.ToString()));
                        str.Clear();
                        continue;
                    }

                    // Argument start.
                    if ((state & BlockParseStates.ParameterList) == BlockParseStates.None && Parser.IsSymbol(text, index, ParserActions.ArgumentStart, ref len))
                    {
                        // Empty token.
                        if (str.Length == 0)
                            return "Unexpected parameter list at index " + index + " in string \"" + text + "\"!";

                        // Already had list.
                        if ((state & BlockParseStates.HadParameterList) != BlockParseStates.None)
                            return "Unexpected parameter list at index " + index + " in string\"" + text + "\"!";

                        // Advance index.
                        index += len;

                        // Add last token as function.
                        block.Elements.Add(new KeyValuePair<BlockElementTypes, object>(BlockElementTypes.Function, str.ToString()));
                        str.Clear();

                        // Now we are listening parameters.
                        state |= BlockParseStates.ParameterList;
                        continue;
                    }

                    // Argument end.
                    if ((state & BlockParseStates.ParameterList) != BlockParseStates.None && Parser.IsSymbol(text, index, ParserActions.ArgumentEnd, ref len))
                    {
                        // Advance index.
                        index += len;

                        // If have token then it's argument.
                        if (str.Length != 0)
                        {
                            block.Elements.Add(new KeyValuePair<BlockElementTypes, object>(BlockElementTypes.Literal, str.ToString()));
                            str.Clear();
                        }

                        // Remove parameter and set end.
                        state &= ~BlockParseStates.ParameterList;
                        state |= BlockParseStates.HadParameterList;
                        continue;
                    }

                    // Argument delimiter.
                    if ((state & BlockParseStates.ParameterList) != BlockParseStates.None && Parser.IsSymbol(text, index, ParserActions.ArgumentDelimiter, ref len))
                    {
                        // Advance index.
                        index += len;

                        // If have token then it's argument.
                        if (str.Length != 0)
                        {
                            block.Elements.Add(new KeyValuePair<BlockElementTypes, object>(BlockElementTypes.Literal, str.ToString()));
                            str.Clear();
                        }

                        // Add delimiter.
                        block.Elements.Add(new KeyValuePair<BlockElementTypes, object>(BlockElementTypes.ParameterDelimiter, null));
                        continue;
                    }
                }

                // Not any control symbol.
                str.Append(text[index]);
                index++;
            }

            // Not allowed to reach here in block.
            if (isBlock)
            {
                // Error.
                return "Reached end of string unexpectedly while parsing block in string \"" + text + "\"!";
            }

            // If have token then it's text.
            if (str.Length != 0)
            {
                block.Elements.Add(new KeyValuePair<BlockElementTypes, object>(BlockElementTypes.Literal, str.ToString()));
                str.Clear();
            }

            // Everything is ok.
            result = block;
            return null;
        }

        #endregion
    }

    #endregion

    #region Block enums

    /// <summary>
    /// All possible states of block parse.
    /// </summary>
    [Flags]
    internal enum BlockParseStates : uint
    {
        /// <summary>
        /// No state has been initialized.
        /// </summary>
        None = 0,

        /// <summary>
        /// Currently have escaped.
        /// </summary>
        Escaped = 1,

        /// <summary>
        /// Parameter list has been opened.
        /// </summary>
        ParameterList = 2,

        /// <summary>
        /// Literal symbol started.
        /// </summary>
        Literal = 4,

        /// <summary>
        /// Already had parameter list.
        /// </summary>
        HadParameterList = 8,
    }

    /// <summary>
    /// List of all block element types.
    /// </summary>
    internal enum BlockElementTypes : int
    {
        /// <summary>
        /// We expect to get an argument.
        /// </summary>
        Argument,

        /// <summary>
        /// We expect to get a variable (text).
        /// </summary>
        Variable,

        /// <summary>
        /// We expect to call a function.
        /// </summary>
        Function,

        /// <summary>
        /// This is another block.
        /// </summary>
        Block,

        /// <summary>
        /// Just text, we don't parse this.
        /// </summary>
        Literal,

        /// <summary>
        /// Delimiter of function parameters.
        /// </summary>
        ParameterDelimiter,
    }

    #endregion

    #region IArgument interface

    /// <summary>
    /// This implements functionality for an argument of message that can be parsed.
    /// </summary>
    public interface IArgument
    {
        #region IArgument members

        /// <summary>
        /// Parse an argument from this object.
        /// </summary>
        /// <param name="key">Keyword for argument.</param>
        /// <param name="message">Message to parse for.</param>
        /// <param name="parser">Parser that is currently processing message.</param>
        /// <returns></returns>
        IArgument ParseArgument(string key, Message message, Parser parser);

        /// <summary>
        /// Parse a variable from this object.
        /// </summary>
        /// <param name="key">Keyword for variable.</param>
        /// <param name="message">Message to parse for.</param>
        /// <param name="parser">Parser that is currently processing message.</param>
        /// <returns></returns>
        string ParseVariable(string key, Message message, Parser parser);

        /// <summary>
        /// Parse a function from this object.
        /// </summary>
        /// <param name="key">Keyword for function.</param>
        /// <param name="args">Arguments for function.</param>
        /// <param name="message">Message to parse for.</param>
        /// <param name="parser">Parser that is currently processing message.</param>
        /// <returns></returns>
        string ParseFunction(string key, string[] args, Message message, Parser parser);

        #endregion
    }

    #endregion

    #region Message class

    /// <summary>
    /// This contains a message that may contain variables to be parsed by the parser.
    /// </summary>
    public sealed class Message
    {
        #region Constructors

        /// <summary>
        /// Create a new empty message.
        /// </summary>
        public Message()
        {
            this._text = "";
            this._block = new Block(this);
        }

        /// <summary>
        /// Create a new message with text.
        /// </summary>
        /// <param name="text">Text to set. Null is not allowed.</param>
        public Message(string text)
        {
            if (text == null)
                throw new ArgumentNullException("text");

            this._text = text;
            int index = 0;
            string r = Block.Parse(this, text, ref index, ref this._block, false);
            if (!string.IsNullOrEmpty(r))
                throw new ArgumentException("text", r);
        }

        /// <summary>
        /// Copy an existing message.
        /// </summary>
        /// <param name="msg">Message to copy.</param>
        public Message(Message msg)
        {
            if (msg == null)
                throw new ArgumentNullException("msg");

            this._text = msg._text;
            this._block = new Block(msg._block, this);
        }

        #endregion

        #region Message members

        /// <summary>
        /// Get or set raw text of message.
        /// </summary>
        public string Text
        {
            get
            {
                // Get current text.
                return this._text;
            }
            set
            {
                // Null is not allowed.
                if (value == null)
                    throw new ArgumentNullException("value");

                // Save some resources.
                if (this._text == value)
                    return;

                // Set new text.
                this._text = value;

                // Calculate cached block.
                int index = 0;
                string r = Block.Parse(this, this._text, ref index, ref this._block, false);
                if (!string.IsNullOrEmpty(r))
                    throw new ArgumentException("value", r);
            }
        }

        /// <summary>
        /// Parse text with given parser. If an error occurs this will throw an exception.
        /// </summary>
        /// <param name="parser">Parser to use. Set null to use default parser.</param>
        /// <returns></returns>
        public string Parse(Parser parser = null)
        {
            if (parser == null)
                parser = new Parser();

            string v = null;
            bool r = this._block.ToString(parser, ref v);
            if (!r)
                throw new InvalidOperationException(v);

            return v;
        }

        /// <summary>
        /// Try to parse text with given parser. If an error occurs we will return false.
        /// </summary>
        /// <param name="parser">Parser to use. Set null to use default parser.</param>
        /// <param name="result">Result. This is error message if false is returned.</param>
        /// <returns></returns>
        public bool TryParse(out string result, Parser parser = null)
        {
            if (parser == null)
                parser = new Parser();

            string v = null;
            bool r = this._block.ToString(parser, ref v);
            result = v;
            return r;
        }
        
        #endregion

        #region Internal members
        
        private string _text;
        private Block _block;

        #endregion
    }

    #endregion

    #region Parser class

    /// <summary>
    /// Implements default message parser behavior.
    /// </summary>
    public class Parser
    {
        #region Constructors

        /// <summary>
        /// Perform static initialization.
        /// </summary>
        static Parser()
        {
            EscapeSymbol = new SymbolList("\\");
            VariableStartSymbol = new SymbolList("<");
            VariableEndSymbol = new SymbolList(">");
            VariableDelimiterSymbol = new SymbolList(".");
            ArgumentStartSymbol = new SymbolList("(");
            ArgumentEndSymbol = new SymbolList(")");
            ArgumentDelimiterSymbol = new SymbolList(",");
            LiteralStartSymbol = new SymbolList("\"");
            LiteralEndSymbol = new SymbolList("\"");
            IgnoreBlockSymbol = new SymbolList(" ", "\t");
            IgnoreAlwaysSymbol = new SymbolList();

            // Register if function.
            Functions["if"] = q =>
            {
                if (q.Length <= 1)
                    return null;

                if (q.Length == 2)
                {
                    Value v = new Value(q[0]);
                    bool qr = false;
                    if (v.TryToBoolean(out qr))
                        return qr ? q[1] : "";
                    return null;
                }

                if (q.Length == 3)
                {
                    Value v = new Value(q[0]);
                    bool qr = false;
                    if (v.TryToBoolean(out qr))
                        return qr ? q[1] : q[2];
                    return null;
                }

                return null;
            };

            // Register randomizer function.
            Functions["rand"] = q =>
            {
                if (q.Length == 0)
                    return new Value(Randomizer.NextDouble()).ToString();
                if (q.Length == 1)
                {
                    Value v = new Value(q[0]);
                    double qv;
                    if (v.TryToDouble(out qv))
                        return Randomizer.Roll(qv) ? "1" : "0";
                    return null;
                }
                else if (q.Length == 2)
                {
                    Value v1 = new Value(q[0]);
                    Value v2 = new Value(q[1]);

                    double qv1, qv2;
                    if (!v1.TryToDouble(out qv1) || !v2.TryToDouble(out qv2))
                        return null;

                    if (qv2 < qv1)
                        return v1.ToString();

                    return new Value(Randomizer.NextDouble() * (qv2 - qv1) + qv1).ToString();
                }

                return null;
            };
            Functions["rnd"] = Functions["rand"];
            Functions["random"] = Functions["rand"];
        }

        /// <summary>
        /// Create a new parser.
        /// </summary>
        public Parser()
        {
        }

        #endregion

        #region Parser members

        /// <summary>
        /// Get or set escape sequence symbol. Default is one backslash.
        /// </summary>
        public static readonly SymbolList EscapeSymbol;

        /// <summary>
        /// Get or set variable block starting symbol. Default is &lt; (less than) sign.
        /// </summary>
        public static readonly SymbolList VariableStartSymbol;

        /// <summary>
        /// Get or set variable block ending symbol. Default is &gt; (greater than) sign.
        /// </summary>
        public static readonly SymbolList VariableEndSymbol;

        /// <summary>
        /// Get or set variable block delimiter symbol. Default is . (dot) symbol.
        /// </summary>
        public static readonly SymbolList VariableDelimiterSymbol;

        /// <summary>
        /// Get or set argument list starting symbol. Default is ( (parenthesis start) sign.
        /// </summary>
        public static readonly SymbolList ArgumentStartSymbol;

        /// <summary>
        /// Get or set argument list ending symbol. Default is ) (parenthesis end) sign.
        /// </summary>
        public static readonly SymbolList ArgumentEndSymbol;

        /// <summary>
        /// Get or set argument list delimiter symbol. Default is , (comma) symbol.
        /// </summary>
        public static readonly SymbolList ArgumentDelimiterSymbol;

        /// <summary>
        /// Get or set literal string starting symbol. Default is " (double quote) sign.
        /// </summary>
        public static readonly SymbolList LiteralStartSymbol;

        /// <summary>
        /// Get or set literal string ending symbol. Default is " (double quote) sign.
        /// </summary>
        public static readonly SymbolList LiteralEndSymbol;

        /// <summary>
        /// Get or set symbols that should be ignored within a block.
        /// </summary>
        public static readonly SymbolList IgnoreBlockSymbol;

        /// <summary>
        /// Get or set symbols that should be ignored everywhere. Same as replacing with empty string.
        /// </summary>
        public static readonly SymbolList IgnoreAlwaysSymbol;

        /// <summary>
        /// Parse an argument by keyword.
        /// </summary>
        /// <param name="message">Message to parse on.</param>
        /// <param name="keyword">Keyword to parse.</param>
        /// <param name="obj">Object to parse on. This is null if base.</param>
        /// <returns></returns>
        public virtual IArgument ParseArgument(Message message, string keyword, IArgument obj)
        {
            // Let object handle this.
            if (obj != null)
                return obj.ParseArgument(keyword, message, this);

            // Check custom arguments.
            return this.Arguments[keyword];
        }

        /// <summary>
        /// Parse a variable by keyword.
        /// </summary>
        /// <param name="message">Message to parse on.</param>
        /// <param name="keyword">Keyword to parse.</param>
        /// <param name="obj">Object to parse on. This is null if base.</param>
        /// <returns></returns>
        public virtual string ParseVariable(Message message, string keyword, IArgument obj)
        {
            // Let object handle this.
            if (obj != null)
                return obj.ParseVariable(keyword, message, this);

            // Invalid.
            return null;
        }

        /// <summary>
        /// Parse a function by keyword.
        /// </summary>
        /// <param name="message">Message to parse on.</param>
        /// <param name="keyword">Keyword to parse.</param>
        /// <param name="args">Arguments of function.</param>
        /// <param name="obj">Object to parse on. This is null if base.</param>
        /// <returns></returns>
        public virtual string ParseFunction(Message message, string keyword, string[] args, IArgument obj)
        {
            // Let object handle this.
            if (obj != null)
                return obj.ParseFunction(keyword, args, message, this);

            Func<string[], string> registered = null;
            if (Functions.TryGetValue(keyword, out registered))
                return registered(args);
            return null;
        }

        /// <summary>
        /// Get or set argument to use in parser. This is also safe - if missing argument
        /// then null is returned and setting null will clear argument.
        /// </summary>
        /// <param name="keyword">Keyword of argument. This is case insensitive.</param>
        /// <returns></returns>
        public IArgument this[string keyword]
        {
            get
            {
                if (keyword == null)
                    throw new ArgumentNullException("keyword");

                IArgument v = null;
                if (this.Arguments.TryGetValue(keyword, out v))
                    return v;
                return null;
            }
            set
            {
                if (keyword == null)
                    throw new ArgumentNullException("keyword");

                if (value == null)
                    this.Arguments.Remove(keyword);
                else
                    this.Arguments[keyword] = value;
            }
        }

        #endregion

        #region Internal members

        /// <summary>
        /// Check if text has symbol for current action.
        /// </summary>
        /// <param name="text">Text to check.</param>
        /// <param name="index">Index in text.</param>
        /// <param name="action">Action to check.</param>
        /// <param name="length">Length of symbol is set here.</param>
        /// <returns></returns>
        internal static bool IsSymbol(string text, int index, ParserActions action, ref int length)
        {
            // Get symbol list for action.
            SymbolList list = null;
            switch (action)
            {
                case ParserActions.Escape: list = EscapeSymbol; break;
                case ParserActions.VariableStart: list = VariableStartSymbol; break;
                case ParserActions.VariableEnd: list = VariableEndSymbol; break;
                case ParserActions.VariableDelimiter: list = VariableDelimiterSymbol; break;
                case ParserActions.ArgumentStart: list = ArgumentStartSymbol; break;
                case ParserActions.ArgumentEnd: list = ArgumentEndSymbol; break;
                case ParserActions.ArgumentDelimiter: list = ArgumentDelimiterSymbol; break;
                case ParserActions.LiteralStart: list = LiteralStartSymbol; break;
                case ParserActions.LiteralEnd: list = LiteralEndSymbol; break;
                case ParserActions.BlockIgnore: list = IgnoreBlockSymbol; break;
                case ParserActions.AlwaysIgnore: list = IgnoreAlwaysSymbol; break;
                default:
                    throw new InvalidOperationException();
            }

            return list.Test(text, index, ref length);
        }

        /// <summary>
        /// Arguments added to this parser.
        /// </summary>
        private readonly Dictionary<string, IArgument> Arguments = new Dictionary<string, IArgument>(StringComparer.OrdinalIgnoreCase);

        /// <summary>
        /// Custom functions.
        /// </summary>
        protected static readonly Dictionary<string, Func<string[], string>> Functions = new Dictionary<string, Func<string[], string>>(StringComparer.OrdinalIgnoreCase);

        #endregion
    }

    #endregion

    #region Parser enums

    /// <summary>
    /// Options for parser.
    /// </summary>
    [Flags]
    public enum ParserFlags : ulong
    {
        None = 0,
    }

    /// <summary>
    /// All actions that the parser can perform.
    /// </summary>
    [Flags]
    internal enum ParserActions : uint
    {
        None = 0,

        /// <summary>
        /// Check for escape symbol.
        /// </summary>
        Escape = 1,

        /// <summary>
        /// Check for variable start symbol.
        /// </summary>
        VariableStart = 2,

        /// <summary>
        /// Check for variable end symbol.
        /// </summary>
        VariableEnd = 4,

        /// <summary>
        /// Check for variable delimiter symbol.
        /// </summary>
        VariableDelimiter = 8,

        /// <summary>
        /// Check for argument list start symbol.
        /// </summary>
        ArgumentStart = 0x10,

        /// <summary>
        /// Check for argument list end symbol.
        /// </summary>
        ArgumentEnd = 0x20,

        /// <summary>
        /// Check for argument delimiter symbol.
        /// </summary>
        ArgumentDelimiter = 0x40,

        /// <summary>
        /// Check for literal start symbol.
        /// </summary>
        LiteralStart = 0x80,

        /// <summary>
        /// Check for literal end symbol.
        /// </summary>
        LiteralEnd = 0x100,

        /// <summary>
        /// Check for block ignore symbols.
        /// </summary>
        BlockIgnore = 0x200,

        /// <summary>
        /// Check for always ignore symbols.
        /// </summary>
        AlwaysIgnore = 0x400,
    }

    #endregion

    #region SymbolList class

    /// <summary>
    /// Represents a list of symbols that can be modified.
    /// </summary>
    public sealed class SymbolList
    {
        #region Constructors

        /// <summary>
        /// Create a new symbol list.
        /// </summary>
        /// <param name="defaultSymbols">Default symbols to add to list.</param>
        internal SymbolList(params string[] defaultSymbols)
        {
            foreach (string x in defaultSymbols)
                this.Add(x);
        }

        #endregion

        #region SymbolList members

        /// <summary>
        /// Add a symbol to this list.
        /// </summary>
        /// <param name="symbol">Symbol to add.</param>
        public void Add(string symbol)
        {
            if (symbol == null)
                throw new ArgumentNullException("symbol");
            if (symbol.Length == 0)
                throw new ArgumentOutOfRangeException("symbol");

            if (this.Symbols.Contains(symbol))
                return;

            this.Symbols.Add(symbol);
        }

        /// <summary>
        /// Remove a symbol from this list.
        /// </summary>
        /// <param name="symbol">Symbol to remove.</param>
        /// <returns></returns>
        public bool Remove(string symbol)
        {
            if (this.Symbols.Remove(symbol))
            {
                return true;
            }
            return false;
        }

        /// <summary>
        /// Clear all added symbols.
        /// </summary>
        public void Clear()
        {
            this.Symbols.Clear();
        }

        /// <summary>
        /// Test if text at index matches any symbols.
        /// </summary>
        /// <param name="text">Text to test.</param>
        /// <param name="index">Index in text where to start testing.</param>
        /// <param name="length">Length of symbol if returned true.</param>
        /// <returns></returns>
        public bool Test(string text, int index, ref int length)
        {
            // Check each symbol.
            foreach (string x in this.Symbols)
            {
                // This matched.
                if (string.Compare(text, index, x, 0, x.Length) == 0)
                {
                    length = x.Length;
                    return true;
                }
            }

            // Didn't find.
            return false;
        }

        /// <summary>
        /// Get count of added symbols.
        /// </summary>
        public int Count
        {
            get
            {
                return this.Symbols.Count;
            }
        }

        /// <summary>
        /// Return an array of symbols.
        /// </summary>
        /// <returns></returns>
        public string[] ToArray()
        {
            return this.Symbols.ToArray();
        }

        #endregion

        #region Internal members

        /// <summary>
        /// List of symbols.
        /// </summary>
        private readonly List<string> Symbols = new List<string>();

        #endregion
    }

    #endregion
}
