using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetScriptFramework
{
    /// <summary>
    /// Parse a memory value from string.
    /// </summary>
    public sealed class MemoryParser
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="MemoryParser" /> class.
        /// </summary>
        /// <param name="formula">The formula.</param>
        /// <exception cref="System.ArgumentNullException">formula</exception>
        public MemoryParser(string formula)
        {
            if (formula == null)
                throw new ArgumentNullException("formula");

            this.Formula = formula;
            this.Build();
        }

        /// <summary>
        /// The formula to parse.
        /// </summary>
        public readonly string Formula;

        /// <summary>
        /// The root block.
        /// </summary>
        private readonly StatementBlock Root = new StatementGroup();

        /// <summary>
        /// Builds this instance.
        /// </summary>
        private void Build()
        {
            StatementBlock b = this.Root;
            string input = this.Formula;

            input = input.Replace(" ", "").ToLowerInvariant();

            while (this.Parse(ref b, ref input))
                continue;

            if (!string.IsNullOrEmpty(input))
                throw new InvalidOperationException();

            if (b != this.Root)
                throw new FormatException("Expected ']' or ')'!");

            this.Root.Finish();
        }

        /// <summary>
        /// Evaluates the value from specified cpu.
        /// </summary>
        /// <param name="cpu">The cpu.</param>
        /// <returns></returns>
        /// <exception cref="System.ArgumentException">this.Formula</exception>
        public IntPtr? Evaluate(CPURegisters cpu)
        {
            List<IntPtr> stack = new List<IntPtr>(4);
            if (!this.Root.Process(cpu, null, stack))
                return null;
            if (stack.Count != 1)
                throw new ArgumentException("this.Formula");
            return stack[0];
        }

        /// <summary>
        /// Base statement.
        /// </summary>
        private abstract class Statement
        {
            /// <summary>
            /// Processes the statement with specified cpu context. Returns false if we couldn't read due to invalid memory address.
            /// </summary>
            /// <param name="cpu">The cpu.</param>
            /// <param name="parent">The parent.</param>
            /// <param name="stack">The stack.</param>
            /// <returns></returns>
            internal abstract bool Process(CPURegisters cpu, StatementBlock parent, List<IntPtr> stack);

            /// <summary>
            /// Gets the amount of stack consumed.
            /// </summary>
            /// <value>
            /// The consumes.
            /// </value>
            internal abstract int Consumes
            {
                get;
            }

            /// <summary>
            /// Gets the amount of stack produced.
            /// </summary>
            /// <value>
            /// The produces.
            /// </value>
            internal abstract int Produces
            {
                get;
            }
        }

        /// <summary>
        /// Accesses registers of CPU.
        /// </summary>
        /// <seealso cref="NetScriptFramework.MemoryParser.Statement" />
        private sealed class StatementRegister : Statement
        {
            /// <summary>
            /// Initializes the <see cref="StatementRegister"/> class.
            /// </summary>
            static StatementRegister()
            {
                var ls = Registers.ToList();
                ls.Sort((u, v) => v.Item1.Length.CompareTo(u.Item1.Length));
                Registers = ls.ToArray();
            }

            /// <summary>
            /// Prevents a default instance of the <see cref="StatementRegister"/> class from being created.
            /// </summary>
            private StatementRegister()
            {

            }

            /// <summary>
            /// Gets the amount of stack consumed.
            /// </summary>
            /// <value>
            /// The consumes.
            /// </value>
            internal override int Consumes
            {
                get
                {
                    return 0;
                }
            }

            /// <summary>
            /// Gets the amount of stack produced.
            /// </summary>
            /// <value>
            /// The produces.
            /// </value>
            internal override int Produces
            {
                get
                {
                    return 1;
                }
            }

            /// <summary>
            /// The function to access.
            /// </summary>
            private Func<CPURegisters, IntPtr> Func = null;

            /// <summary>
            /// Creates the statement from specified input. Returns null if not register access.
            /// </summary>
            /// <param name="input">The input.</param>
            /// <param name="length">The length.</param>
            /// <returns></returns>
            internal static StatementRegister Create(string input, ref int length)
            {
                for (int i = 0; i < Registers.Length; i++)
                {
                    var t = Registers[i];
                    if (input.StartsWith(t.Item1))
                    {
                        length = t.Item1.Length;
                        return new StatementRegister()
                        {
                            Func = t.Item2
                        };
                    }
                }
                return null;
            }

            /// <summary>
            /// Processes the statement with specified cpu context. Returns false if we couldn't read due to invalid memory address.
            /// </summary>
            /// <param name="cpu">The cpu.</param>
            /// <param name="parent">The parent.</param>
            /// <param name="stack">The stack.</param>
            /// <returns></returns>
            internal override bool Process(CPURegisters cpu, StatementBlock parent, List<IntPtr> stack)
            {
                var ptr = this.Func(cpu);
                stack.Add(ptr);
                return true;
            }

            /// <summary>
            /// The registers with their accessors.
            /// </summary>
            private static Tuple<string, Func<CPURegisters, IntPtr>>[] Registers = new Tuple<string, Func<CPURegisters, IntPtr>>[]
            {
                new Tuple<string, Func<CPURegisters, IntPtr>>("rax", q => q.AX),
                new Tuple<string, Func<CPURegisters, IntPtr>>("eax", q => Op(q.AX, u => u & 0xFFFFFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("ax", q => Op(q.AX, u => u & 0xFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("al", q => Op(q.AX, u => u & 0xFF)),

                new Tuple<string, Func<CPURegisters, IntPtr>>("rbx", q => q.BX),
                new Tuple<string, Func<CPURegisters, IntPtr>>("ebx", q => Op(q.BX, u => u & 0xFFFFFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("bx", q => Op(q.BX, u => u & 0xFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("bl", q => Op(q.BX, u => u & 0xFF)),

                new Tuple<string, Func<CPURegisters, IntPtr>>("rcx", q => q.CX),
                new Tuple<string, Func<CPURegisters, IntPtr>>("ecx", q => Op(q.CX, u => u & 0xFFFFFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("cx", q => Op(q.CX, u => u & 0xFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("cl", q => Op(q.CX, u => u & 0xFF)),

                new Tuple<string, Func<CPURegisters, IntPtr>>("rdx", q => q.DX),
                new Tuple<string, Func<CPURegisters, IntPtr>>("edx", q => Op(q.DX, u => u & 0xFFFFFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("dx", q => Op(q.DX, u => u & 0xFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("dl", q => Op(q.DX, u => u & 0xFF)),

                new Tuple<string, Func<CPURegisters, IntPtr>>("rbp", q => q.BP),
                new Tuple<string, Func<CPURegisters, IntPtr>>("ebp", q => Op(q.BP, u => u & 0xFFFFFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("bp", q => Op(q.BP, u => u & 0xFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("bpl", q => Op(q.BP, u => u & 0xFF)),

                new Tuple<string, Func<CPURegisters, IntPtr>>("rsp", q => q.SP),
                new Tuple<string, Func<CPURegisters, IntPtr>>("esp", q => Op(q.SP, u => u & 0xFFFFFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("sp", q => Op(q.SP, u => u & 0xFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("spl", q => Op(q.SP, u => u & 0xFF)),

                new Tuple<string, Func<CPURegisters, IntPtr>>("rsi", q => q.SI),
                new Tuple<string, Func<CPURegisters, IntPtr>>("esi", q => Op(q.SI, u => u & 0xFFFFFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("si", q => Op(q.SI, u => u & 0xFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("sil", q => Op(q.SI, u => u & 0xFF)),

                new Tuple<string, Func<CPURegisters, IntPtr>>("rdi", q => q.DI),
                new Tuple<string, Func<CPURegisters, IntPtr>>("edi", q => Op(q.DI, u => u & 0xFFFFFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("di", q => Op(q.DI, u => u & 0xFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("dil", q => Op(q.DI, u => u & 0xFF)),

                new Tuple<string, Func<CPURegisters, IntPtr>>("rip", q => q.IP),
                new Tuple<string, Func<CPURegisters, IntPtr>>("eip", q => Op(q.IP, u => u & 0xFFFFFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("ip", q => Op(q.IP, u => u & 0xFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("ipl", q => Op(q.IP, u => u & 0xFF)),

                new Tuple<string, Func<CPURegisters, IntPtr>>("r8", q => q.R8),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r8d", q => Op(q.R8, u => u & 0xFFFFFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r8w", q => Op(q.R8, u => u & 0xFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r8b", q => Op(q.R8, u => u & 0xFF)),

                new Tuple<string, Func<CPURegisters, IntPtr>>("r9", q => q.R9),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r9d", q => Op(q.R9, u => u & 0xFFFFFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r9w", q => Op(q.R9, u => u & 0xFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r9b", q => Op(q.R9, u => u & 0xFF)),

                new Tuple<string, Func<CPURegisters, IntPtr>>("r10", q => q.R10),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r10d", q => Op(q.R10, u => u & 0xFFFFFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r10w", q => Op(q.R10, u => u & 0xFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r10b", q => Op(q.R10, u => u & 0xFF)),

                new Tuple<string, Func<CPURegisters, IntPtr>>("r11", q => q.R11),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r11d", q => Op(q.R11, u => u & 0xFFFFFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r11w", q => Op(q.R11, u => u & 0xFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r11b", q => Op(q.R11, u => u & 0xFF)),

                new Tuple<string, Func<CPURegisters, IntPtr>>("r12", q => q.R12),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r12d", q => Op(q.R12, u => u & 0xFFFFFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r12w", q => Op(q.R12, u => u & 0xFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r12b", q => Op(q.R12, u => u & 0xFF)),

                new Tuple<string, Func<CPURegisters, IntPtr>>("r13", q => q.R13),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r13d", q => Op(q.R13, u => u & 0xFFFFFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r13w", q => Op(q.R13, u => u & 0xFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r13b", q => Op(q.R13, u => u & 0xFF)),

                new Tuple<string, Func<CPURegisters, IntPtr>>("r14", q => q.R14),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r14d", q => Op(q.R14, u => u & 0xFFFFFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r14w", q => Op(q.R14, u => u & 0xFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r14b", q => Op(q.R14, u => u & 0xFF)),

                new Tuple<string, Func<CPURegisters, IntPtr>>("r15", q => q.R15),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r15d", q => Op(q.R15, u => u & 0xFFFFFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r15w", q => Op(q.R15, u => u & 0xFFFF)),
                new Tuple<string, Func<CPURegisters, IntPtr>>("r15b", q => Op(q.R15, u => u & 0xFF)),
            };
        }

        /// <summary>
        /// Handles a group of statements.
        /// </summary>
        /// <seealso cref="NetScriptFramework.MemoryParser.Statement" />
        private abstract class StatementBlock : Statement
        {
            /// <summary>
            /// The statements list.
            /// </summary>
            internal List<Statement> Statements = new List<Statement>();

            /// <summary>
            /// The parent, this may be null if root.
            /// </summary>
            internal StatementBlock Parent = null;

            /// <summary>
            /// Grouped statements into one.
            /// </summary>
            internal Statement One = null;

            /// <summary>
            /// Gets the amount of stack consumed.
            /// </summary>
            /// <value>
            /// The consumes.
            /// </value>
            internal override int Consumes
            {
                get
                {
                    return 0;
                }
            }

            /// <summary>
            /// Gets the amount of stack produced.
            /// </summary>
            /// <value>
            /// The produces.
            /// </value>
            internal override int Produces
            {
                get
                {
                    return 1;
                }
            }

            /// <summary>
            /// Finishes this instance.
            /// </summary>
            internal void Finish()
            {
                this.ImplementOperators();

                int stackAmount = this.Consumes;
                for(int i = 0; i < this.Statements.Count; i++)
                {
                    var s = this.Statements[i];
                    if (s.Consumes > stackAmount)
                        throw new FormatException("Trying to consume value that is not present!");
                    stackAmount -= s.Consumes;
                    stackAmount += s.Produces;
                }

                if (stackAmount != this.Produces)
                    throw new FormatException("Producing too many values to parse!");

                if (this.Statements.Count != 1)
                    throw new InvalidOperationException();

                this.One = this.Statements[0];
                this.Statements = null;
            }

            /// <summary>
            /// Implements the operators.
            /// </summary>
            private void ImplementOperators()
            {
                while(true)
                {
                    int bestPriority = int.MinValue;
                    int bestIndex = -1;
                    StatementOperator best = null;

                    for(int i = 0; i < this.Statements.Count; i++)
                    {
                        var s = this.Statements[i];
                        if (!(s is StatementOperator))
                            continue;

                        var ops = (StatementOperator)s;
                        int p = ops.Priority;
                        if(p > bestPriority)
                        {
                            bestPriority = p;
                            bestIndex = i;
                            best = ops;
                        }
                    }

                    if (best == null)
                        break;

                    if (bestIndex == 0 || bestIndex == this.Statements.Count - 1)
                        throw new FormatException("Found operator without an operand!");

                    Statement operand1 = this.Statements[bestIndex - 1];
                    Statement operand2 = this.Statements[bestIndex + 1];
                    this.Statements.RemoveRange(bestIndex - 1, 3);

                    var impl = new StatementOperatorImpl()
                    {
                        Operand1 = operand1,
                        Operand2 = operand2,
                        Operator = best
                    };
                    this.Statements.Insert(bestIndex - 1, impl);
                }
            }

            /// <summary>
            /// Processes the statement with specified cpu context. Returns false if we couldn't read due to invalid memory address.
            /// </summary>
            /// <param name="cpu">The cpu.</param>
            /// <param name="parent">The parent.</param>
            /// <param name="stack">The stack.</param>
            /// <returns></returns>
            internal override bool Process(CPURegisters cpu, StatementBlock parent, List<IntPtr> stack)
            {
                return this.One.Process(cpu, this, stack);
            }
        }

        /// <summary>
        /// Statement group (parenthesis).
        /// </summary>
        /// <seealso cref="NetScriptFramework.MemoryParser.StatementBlock" />
        private sealed class StatementGroup : StatementBlock
        {

        }

        /// <summary>
        /// Tries to read the value at statement.
        /// </summary>
        /// <seealso cref="NetScriptFramework.MemoryParser.StatementBlock" />
        private sealed class StatementRead : StatementBlock
        {
            /// <summary>
            /// Processes the statement with specified cpu context. Returns false if we couldn't read due to invalid memory address.
            /// </summary>
            /// <param name="cpu">The cpu.</param>
            /// <param name="parent">The parent.</param>
            /// <param name="stack">The stack.</param>
            /// <returns></returns>
            internal override bool Process(CPURegisters cpu, StatementBlock parent, List<IntPtr> stack)
            {
                if (!base.Process(cpu, parent, stack))
                    return false;
                var ch = stack[stack.Count - 1];
                if (!Memory.TryReadPointer(ch, ref ch))
                    return false;
                stack[stack.Count - 1] = ch;
                return true;
            }
        }

        /// <summary>
        /// Operator parser.
        /// </summary>
        /// <seealso cref="NetScriptFramework.MemoryParser.Statement" />
        private sealed class StatementOperator : Statement
        {
            internal int Priority = 0;
            internal Func<IntPtr, ulong, IntPtr> Func;

            /// <summary>
            /// Gets the amount of stack consumed.
            /// </summary>
            /// <value>
            /// The consumes.
            /// </value>
            /// <exception cref="System.NotImplementedException"></exception>
            internal override int Consumes
            {
                get
                {
                    throw new NotImplementedException();
                }
            }

            /// <summary>
            /// Gets the amount of stack produced.
            /// </summary>
            /// <value>
            /// The produces.
            /// </value>
            /// <exception cref="System.NotImplementedException"></exception>
            internal override int Produces
            {
                get
                {
                    throw new NotImplementedException();
                }
            }

            /// <summary>
            /// Processes the statement with specified cpu context. Returns false if we couldn't read due to invalid memory address.
            /// </summary>
            /// <param name="cpu">The cpu.</param>
            /// <param name="parent">The parent.</param>
            /// <param name="stack">The stack.</param>
            /// <returns></returns>
            /// <exception cref="System.InvalidOperationException"></exception>
            internal override bool Process(CPURegisters cpu, StatementBlock parent, List<IntPtr> stack)
            {
                throw new InvalidOperationException();
            }

            /// <summary>
            /// Creates the operator from specified input. Returns null if couldn't parse.
            /// </summary>
            /// <param name="input">The input.</param>
            /// <param name="length">The length.</param>
            /// <returns></returns>
            internal static StatementOperator Create(string input, ref int length)
            {
                for(int i = 0; i < Operators.Length; i++)
                {
                    var t = Operators[i];
                    if (!input.StartsWith(t.Item1))
                        continue;
                    length = t.Item1.Length;
                    return new StatementOperator()
                    {
                        Priority = t.Item2,
                        Func = t.Item3
                    };
                }
                return null;
            }

            /// <summary>
            /// The operators.
            /// </summary>
            private static readonly Tuple<string, int, Func<IntPtr, ulong, IntPtr>>[] Operators = new Tuple<string, int, Func<IntPtr, ulong, IntPtr>>[]
            {
                new Tuple<string, int, Func<IntPtr, ulong, IntPtr>>("+", 1, (op1, op2) => Op(op1, u => u + op2)),
                new Tuple<string, int, Func<IntPtr, ulong, IntPtr>>("-", 1, (op1, op2) => Op(op1, u => u - op2)),
                new Tuple<string, int, Func<IntPtr, ulong, IntPtr>>("*", 5, (op1, op2) => Op(op1, u => u * op2)),
                new Tuple<string, int, Func<IntPtr, ulong, IntPtr>>("/", 5, (op1, op2) => Op(op1, u => u / op2)),
                new Tuple<string, int, Func<IntPtr, ulong, IntPtr>>(">>", 10, (op1, op2) => Op(op1, u => u >> (int)op2)),
                new Tuple<string, int, Func<IntPtr, ulong, IntPtr>>("<<", 10, (op1, op2) => Op(op1, u => u << (int)op2)),
            };
        }

        /// <summary>
        /// Implementation of operator.
        /// </summary>
        /// <seealso cref="NetScriptFramework.MemoryParser.Statement" />
        private sealed class StatementOperatorImpl : Statement
        {
            internal Statement Operand1;
            internal Statement Operand2;
            internal StatementOperator Operator;

            /// <summary>
            /// Processes the statement with specified cpu context. Returns false if we couldn't read due to invalid memory address.
            /// </summary>
            /// <param name="cpu">The cpu.</param>
            /// <param name="parent">The parent.</param>
            /// <param name="stack">The stack.</param>
            /// <returns></returns>
            internal override bool Process(CPURegisters cpu, StatementBlock parent, List<IntPtr> stack)
            {
                if (!this.Operand1.Process(cpu, parent, stack))
                    return false;
                IntPtr op1 = stack[stack.Count - 1];
                stack.RemoveAt(stack.Count - 1);

                if (!this.Operand2.Process(cpu, parent, stack))
                    return false;
                IntPtr op2 = stack[stack.Count - 1];
                stack.RemoveAt(stack.Count - 1);

                ulong op2_t = Main.Is64Bit ? op2.ToUInt64() : op2.ToUInt32();

                IntPtr result = this.Operator.Func(op1, op2_t);
                stack.Add(result);
                return true;
            }

            /// <summary>
            /// Gets the amount of stack consumed.
            /// </summary>
            /// <value>
            /// The consumes.
            /// </value>
            internal override int Consumes
            {
                get
                {
                    return 0;
                }
            }

            /// <summary>
            /// Gets the amount of stack produced.
            /// </summary>
            /// <value>
            /// The produces.
            /// </value>
            internal override int Produces
            {
                get
                {
                    return 1;
                }
            }
        }


        /// <summary>
        /// Constant value.
        /// </summary>
        /// <seealso cref="NetScriptFramework.MemoryParser.Statement" />
        private sealed class StatementConstant : Statement
        {
            /// <summary>
            /// Prevents a default instance of the <see cref="StatementConstant"/> class from being created.
            /// </summary>
            private StatementConstant()
            {
            }

            /// <summary>
            /// Gets the amount of stack consumed.
            /// </summary>
            /// <value>
            /// The consumes.
            /// </value>
            internal override int Consumes
            {
                get
                {
                    return 0;
                }
            }

            /// <summary>
            /// Gets the amount of stack produced.
            /// </summary>
            /// <value>
            /// The produces.
            /// </value>
            internal override int Produces
            {
                get
                {
                    return 1;
                }
            }

            /// <summary>
            /// The value.
            /// </summary>
            private IntPtr Value;

            /// <summary>
            /// Processes the statement with specified cpu context. Returns false if we couldn't read due to invalid memory address.
            /// </summary>
            /// <param name="cpu">The cpu.</param>
            /// <param name="parent">The parent.</param>
            /// <param name="stack">The stack.</param>
            /// <returns></returns>
            internal override bool Process(CPURegisters cpu, StatementBlock parent, List<IntPtr> stack)
            {
                stack.Add(this.Value);
                return true;
            }

            /// <summary>
            /// Creates the constant from specified input. Returns null if couldn't parse.
            /// </summary>
            /// <param name="input">The input.</param>
            /// <param name="length">The length.</param>
            /// <returns></returns>
            /// <exception cref="System.FormatException"></exception>
            internal static StatementConstant Create(string input, ref int length)
            {
                int i = 0;
                int j = 0;
                if (input.StartsWith("0x"))
                    i = 2;
                StringBuilder bld = new StringBuilder(16);
                while(i < input.Length)
                {
                    var ch = input[i];
                    if((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f'))
                    {
                        bld.Append(ch);
                        i++;
                        j++;
                        continue;
                    }

                    break;
                }

                if (j == 0)
                    return null;

                ulong u = 0;
                if (!ulong.TryParse(bld.ToString(), System.Globalization.NumberStyles.HexNumber, null, out u))
                    return null;

                IntPtr val;
                if (Main.Is64Bit)
                    val = new IntPtr(unchecked((long)u));
                else
                {
                    if ((u & 0xFFFFFFFF) != u)
                        throw new FormatException(u.ToString("X") + " does not fit into a 32 bit pointer!");
                    uint ux = (uint)u;
                    val = new IntPtr(unchecked((int)ux));
                }

                length = i;
                return new StatementConstant()
                {
                    Value = val
                };
            }
        }

        /// <summary>
        /// Parses the input for specified parent.
        /// </summary>
        /// <param name="parent">The parent.</param>
        /// <param name="input">The input.</param>
        /// <returns></returns>
        /// <exception cref="System.FormatException">
        /// Unexpected ']'!
        /// or
        /// Unexpected ')'!
        /// or
        /// Unexpected input:  + input + !
        /// </exception>
        private bool Parse(ref StatementBlock parent, ref string input)
        {
            if (string.IsNullOrEmpty(input))
                return false;

            if (input[0] == '[')
            {
                var sb = new StatementRead();
                sb.Parent = parent;
                parent.Statements.Add(sb);
                parent = sb;

                input = input.Substring(1);
                return true;
            }

            if(input[0] == ']')
            {
                if (parent == this.Root || !(parent is StatementRead))
                    throw new FormatException("Unexpected ']'!");
                var sb = parent;
                parent = parent.Parent;
                sb.Finish();
                input = input.Substring(1);
                return true;
            }

            if (input[0] == '(')
            {
                var sb = new StatementGroup();
                sb.Parent = parent;
                parent.Statements.Add(sb);
                parent = sb;

                input = input.Substring(1);
                return true;
            }

            if (input[0] == ')')
            {
                if (parent == this.Root || !(parent is StatementGroup))
                    throw new FormatException("Unexpected ')'!");
                var sb = parent;
                parent = parent.Parent;
                sb.Finish();
                input = input.Substring(1);
                return true;
            }

            int len = 0;
            Statement created = StatementOperator.Create(input, ref len);
            if(created != null)
            {
                input = input.Substring(len);
                parent.Statements.Add(created);
                return true;
            }

            created = StatementRegister.Create(input, ref len);
            if(created != null)
            {
                input = input.Substring(len);
                parent.Statements.Add(created);
                return true;
            }

            created = StatementConstant.Create(input, ref len);
            if(created != null)
            {
                input = input.Substring(len);
                parent.Statements.Add(created);
                return true;
            }

            throw new FormatException("Unexpected input: " + input + "!");
        }

        /// <summary>
        /// Apply arithmetic operation to pointer.
        /// </summary>
        /// <param name="ptr">The pointer.</param>
        /// <param name="func">The function.</param>
        /// <returns></returns>
        private static IntPtr Op(IntPtr ptr, Func<ulong, ulong> func)
        {
            ulong u = Main.Is64Bit ? ptr.ToUInt64() : ptr.ToUInt32();
            if (func != null)
                u = func(u);
            if (!Main.Is64Bit)
            {
                uint ux = (uint)(u & 0xFFFFFFFF);
                return new IntPtr(unchecked((int)ux));
            }
            return new IntPtr(unchecked((long)u));
        }
    }
}
