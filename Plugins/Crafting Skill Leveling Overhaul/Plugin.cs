using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework;
using NetScriptFramework.Skyrim;

namespace CraftingSkill
{
    public sealed class CraftingSkillPlugin : Plugin
    {
        public override string Key
        {
            get
            {
                return "craftingskill";
            }
        }

        public override string Name
        {
            get
            {
                return "Crafting skill changes";
            }
        }

        public override string Author
        {
            get
            {
                return "meh321";
            }
        }

        public override int Version
        {
            get
            {
                return 1;
            }
        }

        internal static Settings Settings
        {
            get;
            private set;
        }

        protected override bool Initialize(bool loadedAny)
        {
            var game = NetScriptFramework.Main.Game;
            var debug = CrashLog.Debug;

            if (game == null || game.LibraryVersion < 7 || debug == null)
                throw new InvalidOperationException(this.Name + " requires a newer version of .NET Script Framework! Go update.");

            this.init();

            return true;
        }

        private void init()
        {
            Settings = new Settings();
            Settings.Load();
            
            int temperMode = Settings.TemperFormula;
            int smithMode = Settings.SmithFormula;
            int enchantMode = Settings.EnchantFormula;
            int disenchantMode = Settings.DisenchantFormula;
            int alchemyMode = Settings.AlchemyFormula;

            // Tempering something.
            if(temperMode >= 1 && temperMode <= 3)
                this.InstallHook(50477, 0x115, 6, "FF 90 B8 07 00 00", _Hook_SmithingTemper);

            // Crafting something (creating object).
            if(smithMode >= 1 && smithMode <= 3)
                this.InstallHook(50476, 0x91, 6, "FF 90 B8 07 00 00", _Hook_SmithingCraft);

            // Enchanting something (creating enchantment).
            if(enchantMode >= 2 && enchantMode <= 3)
                this.InstallHook(50450, 0x275, 6, "FF 90 B8 07 00 00", _Hook_Enchanting);

            // Disenchanting.
            if (disenchantMode >= 1 && disenchantMode <= 3)
            {
                var fn = CrashLog.Debug.GetFunctionInfo(11213);
                if (fn == null)
                    throw new InvalidOperationException(this.Name + " failed to write disenchanting hook!");

                fn_Disenchant = new IntPtr((long)(CrashLog.Debug.BaseOffset + fn.Begin));

                this.InstallHook(50459, 0xBA, 6, "FF 90 B8 07 00 00", _Hook_Disenchanting);
            }

            // Alchemy (create potion).
            if(alchemyMode >= 2 && alchemyMode <= 3)
            {
                var fn = CrashLog.Debug.GetFunctionInfo(50424);
                if (fn == null)
                    throw new InvalidOperationException(this.Name + " failed to write alchemy hook (1)!");

                fn_Alchemy1 = new IntPtr((long)(CrashLog.Debug.BaseOffset + fn.Begin));

                fn = CrashLog.Debug.GetFunctionInfo(50463);
                if (fn == null)
                    throw new InvalidOperationException(this.Name + " failed to write alchemy hook (2)!");

                fn_Alchemy2 = new IntPtr((long)(CrashLog.Debug.BaseOffset + fn.Begin));

                this.InstallHook(50449, 0x207, 6, "FF 90 B8 07 00 00", _Hook_Alchemy);
            }
        }

        private static IntPtr fn_Alchemy1;
        private static IntPtr fn_Alchemy2;
        private static IntPtr fn_Disenchant;

        private void InstallHook(ulong vid, int offset, int length, string hex, Action<CPURegisters> func)
        {
            var fn = CrashLog.Debug.GetFunctionInfo(vid);
            if (fn == null)
                throw new InvalidOperationException("Failed to find function for hook in debug library!");

            var addr = new IntPtr((long)(CrashLog.Debug.BaseOffset + fn.Begin + (ulong)offset));
            if (!Memory.VerifyBytes(addr, hex))
                throw new InvalidOperationException("Failed to verify byte pattern! This could mean plugin must be updated or conflict with another plugin.");

            Memory.WriteHook(new HookParameters()
            {
                Address = addr,
                IncludeLength = length,
                ReplaceLength = length,
                Before = func
            });
        }

        private static float Formula_Tempering(float itemAddedCost, float materialCost, float skill)
        {
            int type = Settings.TemperFormula;
            switch(type)
            {
                case 1: // Vanilla
                    {
                        return (float)(Settings.TemperXPMult * Math.Pow(itemAddedCost, Settings.TemperXPExp) + Settings.TemperXPFlat);
                    }

                case 2: // Reworked
                    {
                        return (float)((Settings.TemperXPMult * Math.Pow(materialCost, Settings.TemperXPExp) + Settings.TemperXPFlat) / ((skill + Settings.TemperXPSkillExtra) * Settings.TemperXPSkillMult + 1.0f));
                    }

                case 3: // Reworked2
                    {
                        float avg = (itemAddedCost + materialCost) * 0.5f;
                        return (float)((Settings.TemperXPMult * Math.Pow(avg, Settings.TemperXPExp) + Settings.TemperXPFlat) / ((skill + Settings.TemperXPSkillExtra) * Settings.TemperXPSkillMult + 1.0f));
                    }

                default:
                    return 1.0f;
            }
        }

        private static float Formula_Smithing(float itemCost, float materialCost, float skill)
        {
            int type = Settings.SmithFormula;
            switch (type)
            {
                case 1: // Vanilla
                    {
                        return (float)(Settings.SmithXPMult * Math.Pow(itemCost, Settings.SmithXPExp) + Settings.SmithXPFlat);
                    }

                case 2: // Reworked
                    {
                        return (float)((Settings.SmithXPMult * Math.Pow(materialCost, Settings.SmithXPExp) + Settings.SmithXPFlat) / ((skill + Settings.SmithXPSkillExtra) * Settings.SmithXPSkillMult + 1.0f));
                    }

                case 3: // Reworked2
                    {
                        float avg = (itemCost + materialCost) * 0.5f;
                        return (float)((Settings.SmithXPMult * Math.Pow(avg, Settings.SmithXPExp) + Settings.SmithXPFlat) / ((skill + Settings.SmithXPSkillExtra) * Settings.SmithXPSkillMult + 1.0f));
                    }

                default:
                    return 1.0f;
            }
        }

        private static float Formula_Enchanting(float itemCost, float materialCost, float skill)
        {
            int type = Settings.EnchantFormula;
            switch(type)
            {
                case 2:
                case 3:
                    {
                        float mult1 = (itemCost + Settings.EnchantItemExtraCost) / Settings.EnchantItemAverageCost;
                        float mult2 = (materialCost + Settings.EnchantSoulExtraCost) / Settings.EnchantSoulAverageCost;
                        float flat = Settings.EnchantXPFlat;
                        float div = (skill + Settings.EnchantXPSkillExtra) * Settings.EnchantXPSkillMult + 1.0f;
                        return (mult1 * mult2 + flat) / div;
                    }

                default:
                    return 1.0f;
            }
        }

        private static float Formula_Disenchanting(float itemCost, float enchantmentCost, float skill)
        {
            int type = Settings.DisenchantFormula;
            switch(type)
            {
                // Vanilla.
                case 1: return enchantmentCost * Settings.DisenchantXPMult;

                case 2:
                case 3:
                    {
                        float itemMult = (itemCost + Settings.DisenchantXPItemExtra) / Settings.DisenchantXPItemAverage;
                        float nMult = Settings.DisenchantXPMult;
                        float eMult = enchantmentCost;
                        float skillDiv = (skill + Settings.DisenchantXPSkillExtra) * Settings.DisenchantXPSkillMult + 1.0f;
                        return itemMult * nMult * eMult / skillDiv;
                    }

                default:
                    return 1.0f;
            }
        }

        private static float Formula_Alchemy(List<TESForm> ingredients, MagicItem potion, float skill)
        {
            int type = Settings.AlchemyFormula;
            switch(type)
            {
                case 2:
                    {
                        float cost = 0.0f;
                        if (ingredients.Count != 0)
                            cost = ingredients.Sum(q => Math.Max(0, q.GoldValue));

                        cost = (float)Math.Pow(cost, Settings.AlchemyXPCostExp);

                        float mult = Settings.AlchemyXPMult;
                        float ingredientMult = (float)Math.Pow((float)ingredients.Count, Settings.AlchemyXPExp);
                        
                        float skillDiv = (skill + Settings.AlchemyXPSkillExtra) * Settings.AlchemyXPSkillMult + 1.0f;
                        return (mult * cost * ingredientMult) / skillDiv;
                    }

                case 3:
                    {
                        float cost = 0.0f;
                        if (ingredients.Count != 0)
                            cost = ingredients.Sum(q => Math.Max(0, q.GoldValue));
                        cost = (cost + Math.Max(potion.GoldValue, 0)) * 0.5f;

                        cost = (float)Math.Pow(cost, Settings.AlchemyXPCostExp);

                        float mult = Settings.AlchemyXPMult;
                        float ingredientMult = (float)Math.Pow((float)ingredients.Count, Settings.AlchemyXPExp);
                        
                        float skillDiv = (skill + Settings.AlchemyXPSkillExtra) * Settings.AlchemyXPSkillMult + 1.0f;
                        return (mult * cost * ingredientMult) / skillDiv;
                    }

                default:
                    return 1.0f;
            }
        }

        private static void WriteToDebugFile(string text)
        {
            if ((Settings.DebugMode & 1) != 0)
            {
                using (var f = new System.IO.StreamWriter("Data/NetScriptFramework/Plugins/CraftingSkill.debug.txt", true))
                {
                    var timeStamp = NetScriptFramework.Tools.DateTimeStringConverter.ToLogTimestampString(DateTime.Now, false);
                    f.WriteLine("[" + timeStamp + "] " + text);
                }
            }
            if((Settings.DebugMode & 2) != 0)
            {
                MenuManager.ShowHUDMessage(text, null, true);
            }
        }

        private static void _Hook_SmithingTemper(CPURegisters ctx)
        {
            TESForm item = null;
            {
                var ptr = Memory.ReadPointer(ctx.BX);
                if(ptr != IntPtr.Zero)
                {
                    ptr = Memory.ReadPointer(ptr);
                    item = MemoryObject.FromAddress<TESForm>(ptr);
                }
            }

            double value = 0.0;
            if (item != null)
                value = item.GoldValue;

            if (value < 1.0)
                value = 1.0;

            float oldQuality = Memory.ReadFloat(ctx.BX + 0x18);
            float newQuality = Memory.ReadFloat(ctx.BX + 0x1C);

            var temperForm = MemoryObject.FromAddress<BGSConstructibleObject>(Memory.ReadPointer(ctx.BX + 0x10));
            if (temperForm == null)
                return;

            float amount = 0.0f;
            TESContainer req = temperForm.Requirements;
            int max = req.ContainerEntriesCount;
            for(int i = 0; i < max; i++)
            {
                var entry = req.GetContainerEntry(i);
                if (entry == null)
                    break;

                int gold = entry.Item.GoldValue;
                if (gold <= 0)
                    continue;

                amount += gold * entry.Count;
            }

            var plr = PlayerCharacter.Instance;
            float skill = 5.0f;
            if (plr != null)
                skill = plr.GetActorValue(ActorValueIndices.Smithing);

            float xp = Formula_Tempering((newQuality - oldQuality) * (float)value, amount, skill);
            if (xp < 0.0f)
                xp = 0.0f;

            if(Settings.DebugMode > 0)
                WriteToDebugFile("Tempering: original XP was " + ctx.XMM2f.ToString(System.Globalization.CultureInfo.InvariantCulture) + " and we replaced it with " + xp.ToString(System.Globalization.CultureInfo.InvariantCulture));

            ctx.XMM2f = xp;
        }

        private static void _Hook_SmithingCraft(CPURegisters ctx)
        {
            var temperForm = MemoryObject.FromAddress<BGSConstructibleObject>(ctx.SI);
            if (temperForm == null)
                return;

            float amount = 0.0f;
            TESContainer req = temperForm.Requirements;
            int max = req.ContainerEntriesCount;
            for (int i = 0; i < max; i++)
            {
                var entry = req.GetContainerEntry(i);
                if (entry == null)
                    break;

                int gold = entry.Item.GoldValue;
                if (gold <= 0)
                    continue;

                amount += gold * entry.Count;
            }

            var plr = PlayerCharacter.Instance;
            float skill = 5.0f;
            if (plr != null)
                skill = plr.GetActorValue(ActorValueIndices.Smithing);

            float value = 0.0f;
            var item = temperForm.CreatedItem;
            if (item != null)
                value = item.GoldValue * temperForm.CreatedCount;

            if (value < 0.0f)
                value = 0.0f;

            float xp = Formula_Smithing(value, amount, skill);
            if (xp < 0.0f)
                xp = 0.0f;

            if (Settings.DebugMode > 0)
                WriteToDebugFile("Smithing: original XP was " + ctx.XMM2f.ToString(System.Globalization.CultureInfo.InvariantCulture) + " and we replaced it with " + xp.ToString(System.Globalization.CultureInfo.InvariantCulture));

            ctx.XMM2f = xp;
        }

        private static void _Hook_Enchanting(CPURegisters ctx)
        {
            var item = MemoryObject.FromAddress<TESForm>(Memory.ReadPointer(ctx.R15));
            var soul = MemoryObject.FromAddress<TESForm>(Memory.ReadPointer(Memory.ReadPointer(ctx.BX + 0x18)));

            float skill = 5.0f;
            var plr = PlayerCharacter.Instance;
            if (plr != null)
                skill = plr.GetActorValue(ActorValueIndices.Enchanting);
            float xp = Formula_Enchanting(Math.Max(0, item.GoldValue), Math.Max(0, soul.GoldValue), skill);
            if (xp < 0.0f)
                xp = 0.0f;

            if (Settings.DebugMode > 0)
                WriteToDebugFile("Enchanting: original XP was " + ctx.XMM2f.ToString(System.Globalization.CultureInfo.InvariantCulture) + " and we replaced it with " + xp.ToString(System.Globalization.CultureInfo.InvariantCulture));

            ctx.XMM2f = xp;
        }

        private static void _Hook_Disenchanting(CPURegisters ctx)
        {
            var item = MemoryObject.FromAddress<TESForm>(Memory.ReadPointer(ctx.R14));
            var enchantment = MemoryObject.FromAddress<EffectSetting>(ctx.SI);

            float skill = 5.0f;
            var plr = PlayerCharacter.Instance;
            if (plr != null)
                skill = plr.GetActorValue(ActorValueIndices.Enchanting);

            float enchantmentValue = Memory.InvokeCdeclF(fn_Disenchant, enchantment.Address, 0);

            float xp = Formula_Disenchanting(Math.Max(0, item.GoldValue), enchantmentValue, skill);
            if (xp < 0.0f)
                xp = 0.0f;

            if (Settings.DebugMode > 0)
                WriteToDebugFile("Disenchanting: original XP was " + ctx.XMM2f.ToString(System.Globalization.CultureInfo.InvariantCulture) + " and we replaced it with " + xp.ToString(System.Globalization.CultureInfo.InvariantCulture));

            ctx.XMM2f = xp;
        }

        private static void _Hook_Alchemy(CPURegisters ctx)
        {
            var menu = ctx.R13;
            var menuArray = menu + 280;

            List<TESForm> ingredients = new List<TESForm>(4);

            using (var alloc = Memory.Allocate(0x20))
            {
                Memory.InvokeCdecl(fn_Alchemy1, menuArray, alloc.Address);
                Memory.InvokeCdecl(fn_Alchemy2, menuArray, alloc.Address + 0x10);
                var v96 = Memory.ReadPointer(alloc.Address);
                var v28 = Memory.ReadPointer(alloc.Address + 0x10);
                while (v28 != v96)
                {
                    var v30 = Memory.ReadPointer(Memory.ReadPointer(Memory.ReadPointer(menu + 256) + 16 * Memory.ReadInt32(v96)));

                    var item = MemoryObject.FromAddress<TESForm>(v30);
                    ingredients.Add(item);

                    v96 = v96 + 4;
                }
            }

            var potion = MemoryObject.FromAddress<MagicItem>(Memory.ReadPointer(ctx.SP + 0x50));

            float skill = 5.0f;
            var plr = PlayerCharacter.Instance;
            if (plr != null)
                skill = plr.GetActorValue(ActorValueIndices.Alchemy);

            float xp = Formula_Alchemy(ingredients, potion, skill);
            if (xp < 0.0f)
                xp = 0.0f;

            if (Settings.DebugMode > 0)
                WriteToDebugFile("Alchemy: original XP was " + ctx.XMM2f.ToString(System.Globalization.CultureInfo.InvariantCulture) + " and we replaced it with " + xp.ToString(System.Globalization.CultureInfo.InvariantCulture));

            ctx.XMM2f = xp;
        }
    }
}
