using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetScriptFramework.Tools
{
    #region Randomizer class

    /// <summary>
    /// Random number generator. Thread safe.
    /// </summary>
    public static class Randomizer
    {
        #region Randomizer members

        /// <summary>
        /// Generate a double between 0 and 1.
        /// </summary>
        /// <returns></returns>
        public static double NextDouble()
        {
            Init();
            return RNG.NextDouble();
        }

        /// <summary>
        /// Generate an integer, max is exclusive.
        /// </summary>
        /// <param name="min">Inclusive minimum value.</param>
        /// <param name="max">Exclusive maximum value.</param>
        /// <returns></returns>
        public static int NextInt(int min, int max)
        {
            Init();
            return RNG.Next(min, max);
        }

        /// <summary>
        /// Roll chance. Chance must be between 0 and 1.
        /// </summary>
        /// <param name="chance">Chance to roll.</param>
        /// <returns></returns>
        public static bool Roll(double chance)
        {
            if (chance <= 0.0)
                return false;
            if (chance >= 1.0)
                return true;
            return NextDouble() <= chance;
        }

        /// <summary>
        /// Get random entry from a list and remove that entry from the list.
        /// </summary>
        /// <typeparam name="T">Type of variable.</typeparam>
        /// <param name="list">List to get from.</param>
        /// <param name="remove">Remove the entry from list afterwards.</param>
        /// <returns></returns>
        /// <exception cref="System.ArgumentNullException">list</exception>
        /// <exception cref="System.ArgumentOutOfRangeException">list</exception>
        public static T NextEntry<T>(IList<T> list, bool remove = true)
        {
            if (list == null)
                throw new ArgumentNullException("list");
            if (list.Count == 0)
                throw new ArgumentOutOfRangeException("list");

            int chosen = 0;
            if (list.Count != 1)
                chosen = NextInt(0, list.Count);

            T obj = list[chosen];
            if (remove)
                list.RemoveAt(chosen);

            return obj;
        }

        /// <summary>
        /// Get random entry from a list and remove that entry from the list. This is roulette
        /// wheel selection where double is the weight of entry.
        /// </summary>
        /// <typeparam name="T">Type of variable.</typeparam>
        /// <param name="list">List to get from.</param>
        /// <param name="remove">Remove the entry from list afterwards.</param>
        /// <returns></returns>
        /// <exception cref="System.ArgumentNullException">list</exception>
        /// <exception cref="System.ArgumentOutOfRangeException">list</exception>
        public static T NextEntry<T>(IList<KeyValuePair<T, double>> list, bool remove = true)
        {
            if (list == null)
                throw new ArgumentNullException("list");
            if (list.Count == 0)
                throw new ArgumentOutOfRangeException("list");

            double max = list.Sum(q => q.Value);
            return NextEntry<T>(list, ref max, remove);
        }

        /// <summary>
        /// Get random entry from a list and remove that entry from the list. This is roulette
        /// wheel selection where double is the weight of entry.
        /// </summary>
        /// <typeparam name="T">Type of variable.</typeparam>
        /// <param name="list">List to get from.</param>
        /// <param name="max">Precalculated sum.</param>
        /// <param name="remove">Remove the entry from list afterwards.</param>
        /// <returns></returns>
        /// <exception cref="System.ArgumentNullException">list</exception>
        /// <exception cref="System.ArgumentOutOfRangeException">list</exception>
        public static T NextEntry<T>(IList<KeyValuePair<T, double>> list, ref double max, bool remove = true)
        {
            if (list == null)
                throw new ArgumentNullException("list");
            if (list.Count == 0)
                throw new ArgumentOutOfRangeException("list");

            double chooseValue = max * NextDouble();

            int chosen = -1;
            for (int i = 0; i < list.Count; i++)
            {
                if (list[i].Value <= 0.0)
                    continue;

                chosen = i;
                chooseValue -= list[i].Value;
                if (chooseValue < 0.0)
                {
                    max -= list[i].Value;
                    break;
                }
            }

            if (chosen == -1)
                chosen = 0;

            T obj = list[chosen].Key;
            if (remove)
                list.RemoveAt(chosen);

            return obj;
        }

        /// <summary>
        /// Get random entry from a list and remove that entry from the list. This is roulette
        /// wheel selection where double is the weight of entry.
        /// </summary>
        /// <typeparam name="T">Type of variable.</typeparam>
        /// <param name="list">List to get from.</param>
        /// <param name="weightSelector">Weight selector function.</param>
        /// <param name="max">Precalculated sum.</param>
        /// <param name="remove">Remove the entry from list afterwards.</param>
        /// <returns></returns>
        /// <exception cref="System.ArgumentNullException">list</exception>
        /// <exception cref="System.ArgumentOutOfRangeException">list</exception>
        public static T NextEntry<T>(IList<T> list, Func<T, double> weightSelector, ref double max, bool remove = true)
        {
            if (list == null)
                throw new ArgumentNullException("list");
            if (list.Count == 0)
                throw new ArgumentOutOfRangeException("list");

            double chooseValue = max * NextDouble();

            int chosen = -1;
            for (int i = 0; i < list.Count; i++)
            {
                double w = weightSelector(list[i]);
                if (w <= 0.0)
                    continue;

                chosen = i;
                chooseValue -= w;
                if (chooseValue < 0.0)
                {
                    max -= w;
                    break;
                }
            }

            if (chosen == -1)
                chosen = 0;

            T obj = list[chosen];
            if (remove)
                list.RemoveAt(chosen);

            return obj;
        }

        #endregion

        #region Internal members

        /// <summary>
        /// Make sure generator is initialize for current thread.
        /// </summary>
        private static void Init()
        {
            if (RNG != null)
                return;

            lock (Locker)
            {
                RNG = new System.Random(Generator.Next(0, int.MaxValue));
            }
        }

        /// <summary>
        /// RNG for current thread.
        /// </summary>
        [ThreadStatic]
        private static System.Random RNG = null;

        /// <summary>
        /// Locker for generating a generator.
        /// </summary>
        private static readonly object Locker = new object();

        /// <summary>
        /// Seed generator.
        /// </summary>
        private static readonly System.Random Generator = new System.Random();

        #endregion
    }

    #endregion
}
