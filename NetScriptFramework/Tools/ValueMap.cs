using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetScriptFramework.Tools
{
    #region ValueMap class

    /// <summary>
    /// Implements a map for values with case insensitive string key.
    /// </summary>
    public sealed class ValueMap : IDictionary<string, Value>
    {
        #region Constructors

        /// <summary>
        /// Create a new empty value map.
        /// </summary>
        public ValueMap()
        {
            this.internalDict = new Dictionary<string, Value>(StringComparer.OrdinalIgnoreCase);
        }

        /// <summary>
        /// Copy an existing value map.
        /// </summary>
        /// <param name="map">Map to copy.</param>
        /// <exception cref="System.ArgumentNullException">map</exception>
        public ValueMap(ValueMap map)
        {
            if (map == null)
                throw new ArgumentNullException("map");

            this.internalDict = new Dictionary<string, Value>(map.internalDict);
        }

        #endregion

        #region ValueMap members

        /// <summary>
        /// Add a value to map.
        /// </summary>
        /// <param name="key">Key of value.</param>
        /// <param name="value">Value to add.</param>
        /// <exception cref="System.ArgumentNullException">
        /// key
        /// or
        /// value
        /// </exception>
        public void Add(string key, Value value)
        {
            if (key == null)
                throw new ArgumentNullException("key");
            if (value == null)
                throw new ArgumentNullException("value");

            internalDict.Add(key, value);
        }

        /// <summary>
        /// Check if map contains a key.
        /// </summary>
        /// <param name="key">Key to check.</param>
        /// <returns>
        /// true if the <see cref="T:System.Collections.Generic.IDictionary`2" /> contains an element with the key; otherwise, false.
        /// </returns>
        /// <exception cref="System.ArgumentNullException">key</exception>
        public bool ContainsKey(string key)
        {
            if (key == null)
                throw new ArgumentNullException("key");

            return internalDict.ContainsKey(key);
        }

        /// <summary>
        /// Get all added keys.
        /// </summary>
        public ICollection<string> Keys
        {
            get { return internalDict.Keys; }
        }

        /// <summary>
        /// Try to get value and return if we did.
        /// </summary>
        /// <param name="key">Key to get by.</param>
        /// <param name="value">Value to set.</param>
        /// <returns></returns>
        public bool TryGetValue(string key, out Value value)
        {
            return internalDict.TryGetValue(key, out value);
        }

        /// <summary>
        /// Get all added values.
        /// </summary>
        public ICollection<Value> Values
        {
            get { return internalDict.Values; }
        }

        /// <summary>
        /// Get or set value by key. This is safe and will return null if value is not present.
        /// Key must not be null! Setting value to null will remove it from the map.
        /// </summary>
        /// <value>
        /// The <see cref="Value"/>.
        /// </value>
        /// <param name="key">Key to use. Must not be null.</param>
        /// <returns></returns>
        /// <exception cref="System.ArgumentNullException">
        /// key
        /// </exception>
        public Value this[string key]
        {
            get
            {
                if (key == null)
                    throw new ArgumentNullException("key");

                Value v = null;
                if (this.TryGetValue(key, out v))
                    return v;
                return null;
            }
            set
            {
                if (key == null)
                    throw new ArgumentNullException("key");

                if (value == null)
                    this.Remove(key);
                else
                    internalDict[key] = value;
            }
        }

        #endregion

        #region Access members

        /// <summary>
        /// Try convert value by key and return if we did.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="result">Result is set here.</param>
        /// <returns></returns>
        public bool TryToBool(string key, out bool result)
        {
            result = false;
            var value = this[key];
            if (value == null)
                return false;

            return value.TryToBoolean(out result);
        }

        /// <summary>
        /// Try convert value by key and return if we did.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="result">Result is set here.</param>
        /// <returns></returns>
        public bool TryToByte(string key, out byte result)
        {
            result = 0;
            var value = this[key];
            if (value == null)
                return false;

            return value.TryToByte(out result);
        }

        /// <summary>
        /// Try convert value by key and return if we did.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="result">Result is set here.</param>
        /// <returns></returns>
        public bool TryToChar(string key, out char result)
        {
            result = '\0';
            var value = this[key];
            if (value == null)
                return false;

            return value.TryToChar(out result);
        }

        /// <summary>
        /// Try convert value by key and return if we did.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="result">Result is set here.</param>
        /// <returns></returns>
        public bool TryToInt16(string key, out short result)
        {
            result = 0;
            var value = this[key];
            if (value == null)
                return false;

            return value.TryToInt16(out result);
        }

        /// <summary>
        /// Try convert value by key and return if we did.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="result">Result is set here.</param>
        /// <returns></returns>
        public bool TryToUInt16(string key, out ushort result)
        {
            result = 0;
            var value = this[key];
            if (value == null)
                return false;

            return value.TryToUInt16(out result);
        }

        /// <summary>
        /// Try convert value by key and return if we did.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="result">Result is set here.</param>
        /// <returns></returns>
        public bool TryToInt32(string key, out int result)
        {
            result = 0;
            var value = this[key];
            if (value == null)
                return false;

            return value.TryToInt32(out result);
        }

        /// <summary>
        /// Try convert value by key and return if we did.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="result">Result is set here.</param>
        /// <returns></returns>
        public bool TryToUInt32(string key, out uint result)
        {
            result = 0;
            var value = this[key];
            if (value == null)
                return false;

            return value.TryToUInt32(out result);
        }

        /// <summary>
        /// Try convert value by key and return if we did.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="result">Result is set here.</param>
        /// <returns></returns>
        public bool TryToInt64(string key, out long result)
        {
            result = 0;
            var value = this[key];
            if (value == null)
                return false;

            return value.TryToInt64(out result);
        }

        /// <summary>
        /// Try convert value by key and return if we did.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="result">Result is set here.</param>
        /// <returns></returns>
        public bool TryToUInt64(string key, out ulong result)
        {
            result = 0;
            var value = this[key];
            if (value == null)
                return false;

            return value.TryToUInt64(out result);
        }

        /// <summary>
        /// Try convert value by key and return if we did.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="result">Result is set here.</param>
        /// <returns></returns>
        public bool TryToSingle(string key, out float result)
        {
            result = 0.0f;
            var value = this[key];
            if (value == null)
                return false;

            return value.TryToSingle(out result);
        }

        /// <summary>
        /// Try convert value by key and return if we did.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="result">Result is set here.</param>
        /// <returns></returns>
        public bool TryToDouble(string key, out double result)
        {
            result = 0.0;
            var value = this[key];
            if (value == null)
                return false;

            return value.TryToDouble(out result);
        }

        /// <summary>
        /// Try convert value by key and return if we did.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="result">Result is set here.</param>
        /// <returns></returns>
        public bool TryToDecimal(string key, out decimal result)
        {
            result = 0;
            var value = this[key];
            if (value == null)
                return false;

            return value.TryToDecimal(out result);
        }

        /// <summary>
        /// Try convert value by key and return if we did.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="result">Result is set here.</param>
        /// <returns></returns>
        public bool TryToString(string key, out string result)
        {
            result = null;
            var value = this[key];
            if (value == null)
                return false;

            result = value.ToString();
            return true;
        }

        /// <summary>
        /// Try convert value by key and return if we did.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="result">Result is set here.</param>
        /// <returns></returns>
        public bool TryToSByte(string key, out sbyte result)
        {
            result = 0;
            var value = this[key];
            if (value == null)
                return false;

            return value.TryToSByte(out result);
        }

        /// <summary>
        /// Try convert value by key and return if we did.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="result">Result is set here.</param>
        /// <returns></returns>
        public bool TryToDateTime(string key, out DateTime result)
        {
            result = new DateTime();
            var value = this[key];
            if (value == null)
                return false;

            return value.TryToDateTime(out result);
        }

        /// <summary>
        /// Try convert value by key.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="error">If missing or couldn't convert return this.</param>
        /// <returns></returns>
        public bool ToBool(string key, bool error = false)
        {
            bool result;
            if (this.TryToBool(key, out result))
                return result;
            return error;
        }

        /// <summary>
        /// Try convert value by key.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="error">If missing or couldn't convert return this.</param>
        /// <returns></returns>
        public byte ToByte(string key, byte error = 0)
        {
            byte result;
            if (this.TryToByte(key, out result))
                return result;
            return error;
        }

        /// <summary>
        /// Try convert value by key.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="error">If missing or couldn't convert return this.</param>
        /// <returns></returns>
        public char ToChar(string key, char error = '\0')
        {
            char result;
            if (this.TryToChar(key, out result))
                return result;
            return error;
        }

        /// <summary>
        /// Try convert value by key.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="error">If missing or couldn't convert return this.</param>
        /// <returns></returns>
        public short ToInt16(string key, short error = 0)
        {
            short result;
            if (this.TryToInt16(key, out result))
                return result;
            return error;
        }

        /// <summary>
        /// Try convert value by key.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="error">If missing or couldn't convert return this.</param>
        /// <returns></returns>
        public ushort ToUInt16(string key, ushort error = 0)
        {
            ushort result;
            if (this.TryToUInt16(key, out result))
                return result;
            return error;
        }

        /// <summary>
        /// Try convert value by key.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="error">If missing or couldn't convert return this.</param>
        /// <returns></returns>
        public int ToInt32(string key, int error = 0)
        {
            int result;
            if (this.TryToInt32(key, out result))
                return result;
            return error;
        }

        /// <summary>
        /// Try convert value by key.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="error">If missing or couldn't convert return this.</param>
        /// <returns></returns>
        public uint ToUInt32(string key, uint error = 0)
        {
            uint result;
            if (this.TryToUInt32(key, out result))
                return result;
            return error;
        }

        /// <summary>
        /// Try convert value by key.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="error">If missing or couldn't convert return this.</param>
        /// <returns></returns>
        public long ToInt64(string key, long error = 0)
        {
            long result;
            if (this.TryToInt64(key, out result))
                return result;
            return error;
        }

        /// <summary>
        /// Try convert value by key.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="error">If missing or couldn't convert return this.</param>
        /// <returns></returns>
        public ulong ToUInt64(string key, ulong error = 0)
        {
            ulong result;
            if (this.TryToUInt64(key, out result))
                return result;
            return error;
        }

        /// <summary>
        /// Try convert value by key.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="error">If missing or couldn't convert return this.</param>
        /// <returns></returns>
        public float ToSingle(string key, float error = 0.0f)
        {
            float result;
            if (this.TryToSingle(key, out result))
                return result;
            return error;
        }

        /// <summary>
        /// Try convert value by key.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="error">If missing or couldn't convert return this.</param>
        /// <returns></returns>
        public double ToDouble(string key, double error = 0.0)
        {
            double result;
            if (this.TryToDouble(key, out result))
                return result;
            return error;
        }

        /// <summary>
        /// Try convert value by key.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="error">If missing or couldn't convert return this.</param>
        /// <returns></returns>
        public decimal ToDecimal(string key, decimal error = 0.0m)
        {
            decimal result;
            if (this.TryToDecimal(key, out result))
                return result;
            return error;
        }

        /// <summary>
        /// Try convert value by key.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="error">If missing or couldn't convert return this.</param>
        /// <returns></returns>
        public string ToString(string key, string error = null)
        {
            string result;
            if (this.TryToString(key, out result))
                return result;
            return error;
        }

        /// <summary>
        /// Try convert value by key.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="error">If missing or couldn't convert return this.</param>
        /// <returns></returns>
        public sbyte ToSByte(string key, sbyte error = 0)
        {
            sbyte result;
            if (this.TryToSByte(key, out result))
                return result;
            return error;
        }

        /// <summary>
        /// Try convert value by key.
        /// </summary>
        /// <param name="key">Key to get.</param>
        /// <param name="error">If missing or couldn't convert return this.</param>
        /// <returns></returns>
        public DateTime ToDateTime(string key, DateTime error = new DateTime())
        {
            DateTime result;
            if (this.TryToDateTime(key, out result))
                return result;
            return error;
        }

        #endregion

        #region ICollection members

        /// <summary>
        /// Add item to map.
        /// </summary>
        /// <param name="item">Item to add.</param>
        public void Add(KeyValuePair<string, Value> item)
        {
            internalDict.Add(item.Key, item.Value);
        }

        /// <summary>
        /// Clear map.
        /// </summary>
        public void Clear()
        {
            internalDict.Clear();
        }

        /// <summary>
        /// Check if map contains item.
        /// </summary>
        /// <param name="item">Item to check.</param>
        /// <returns></returns>
        public bool Contains(KeyValuePair<string, Value> item)
        {
            if (item.Key == null)
                return false;
            if (item.Value == null)
                return false;

            return this[item.Key] == item.Value;
        }

        /// <summary>
        /// Get count of entries.
        /// </summary>
        public int Count
        {
            get
            {
                return internalDict.Count;
            }
        }

        /// <summary>
        /// Check if map is read only.
        /// </summary>
        public bool IsReadOnly
        {
            get
            {
                return false;
            }
        }

        /// <summary>
        /// Remove item from map.
        /// </summary>
        /// <param name="item">Item to remove.</param>
        /// <returns></returns>
        public bool Remove(KeyValuePair<string, Value> item)
        {
            if (item.Key == null || item.Value == null)
                return false;

            Value v = this[item.Key];
            if (v == item.Value)
                return this.Remove(item.Key);
            return false;
        }

        /// <summary>
        /// Remove value from map.
        /// </summary>
        /// <param name="key">Key to remove by.</param>
        /// <returns></returns>
        public bool Remove(string key)
        {
            if (key == null)
                throw new ArgumentNullException("key");

            return this.internalDict.Remove(key);
        }

        /// <summary>
        /// Copy current values to array.
        /// </summary>
        /// <param name="array">Array to copy to.</param>
        /// <param name="arrayIndex">Index in array when to start copying.</param>
        public void CopyTo(KeyValuePair<string, Value>[] array, int arrayIndex)
        {
            KeyValuePair<string, Value>[] data = this.internalDict.ToArray();
            Buffer.BlockCopy(data, 0, array, arrayIndex, data.Length);
        }

        #endregion

        #region IEnumerable members

        /// <summary>
        /// Get enumerator.
        /// </summary>
        /// <returns></returns>
        public IEnumerator<KeyValuePair<string, Value>> GetEnumerator()
        {
            return internalDict.GetEnumerator();
        }

        /// <summary>
        /// Get enumerator.
        /// </summary>
        /// <returns></returns>
        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return internalDict.GetEnumerator();
        }

        #endregion

        #region Internal members

        /// <summary>
        /// Internal values.
        /// </summary>
        private readonly Dictionary<string, Value> internalDict;

        #endregion
    }

    #endregion
}
