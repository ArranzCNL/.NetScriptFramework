using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework.Tools;
using NetScriptFramework.SkyrimSE;

namespace CraftingSkill
{
    public sealed class Settings
    {
        #region Tempering

        [ConfigValue("TemperFormula", "Temper formula", "This says which formula to use for tempering.\n0 = disabled, don't overwrite temper XP gain at all.\n1 = vanilla \"TemperXPMult * ItemAddedGoldValue ^ TemperXPExp + TemperXPFlat\"\n2 = reworked \"(TemperXPMult * UsedMaterialsGoldValue ^ TemperXPExp + TemperXPFlat) / ((SkillLevel + TemperXPSkillExtra) * TemperXPSkillMult + 1)\n3 = same as reworked but instead of only UsedMaterialsGoldValue we average that with ItemAddedGoldValue.")]
        public int TemperFormula
        {
            get;
            set;
        } = 2;

        [ConfigValue("TemperXPMult", "Temper XP multiplier", "This is the multiplier component of the temper formula chosen above.")]
        public float TemperXPMult
        {
            get;
            set;
        } = 2.0f;

        [ConfigValue("TemperXPExp", "Temper XP exponent", "This is the exponent component of the temper formula chosen above.")]
        public float TemperXPExp
        {
            get;
            set;
        } = 1.1f;

        [ConfigValue("TemperXPFlat", "Temper XP flat", "This is the flat amount component of the temper formula chosen above.")]
        public float TemperXPFlat
        {
            get;
            set;
        } = 0.0f;

        [ConfigValue("TemperXPSkillExtra", "Temper XP skill extra", "This is the extra skill component of the temper formula chosen above. What it does is pretend our smithing skill is this much higher than it really is. The purpose of this is to make sure we don't get massive amount of experience on level 5 and then suddenly half experience at level 10.")]
        public float TemperXPSkillExtra
        {
            get;
            set;
        } = 10.0f;

        [ConfigValue("TemperXPSkillMult", "Temper XP skill multiplier", "This is the skill multiplier component of the temper formula chosen above.")]
        public float TemperXPSkillMult
        {
            get;
            set;
        } = 0.05f;

        #endregion

        #region Smithing

        [ConfigValue("SmithFormula", "Smith formula", "This says which formula to use for smithing (crafting objects).\n0 = disabled, don't overwrite smithing XP gain at all.\n1 = vanilla \"SmithXPMult * CreatedItemGoldValue ^ SmithXPExp + SmithXPFlat\"\n2 = reworked \"(SmithXPMult * UsedMaterialsGoldValue ^ SmithXPExp + SmithXPFlat) / ((SkillLevel + SmithXPSkillExtra) * SmithXPSkillMult + 1)\n3 = same as reworked but instead of only UsedMaterialsGoldValue we average that with CreatedItemGoldValue.")]
        public int SmithFormula
        {
            get;
            set;
        } = 2;

        [ConfigValue("SmithXPMult", "Smith XP multiplier", "This is the multiplier component of the smithing formula chosen above.")]
        public float SmithXPMult
        {
            get;
            set;
        } = 3.0f;

        [ConfigValue("SmithXPExp", "Smith XP exponent", "This is the exponent component of the smithing formula chosen above.")]
        public float SmithXPExp
        {
            get;
            set;
        } = 1.1f;

        [ConfigValue("SmithXPFlat", "Smith XP flat", "This is the flat amount component of the smithing formula chosen above.")]
        public float SmithXPFlat
        {
            get;
            set;
        } = 0.0f;

        [ConfigValue("SmithXPSkillExtra", "Smith XP skill extra", "This is the extra skill component of the smithing formula chosen above. What it does is pretend our smithing skill is this much higher than it really is. The purpose of this is to make sure we don't get massive amount of experience on level 5 and then suddenly half experience at level 10.")]
        public float SmithXPSkillExtra
        {
            get;
            set;
        } = 10.0f;

        [ConfigValue("SmithXPSkillMult", "Smith XP skill multiplier", "This is the skill multiplier component of the smithing formula chosen above.")]
        public float SmithXPSkillMult
        {
            get;
            set;
        } = 0.05f;

        #endregion

        #region Enchanting

        [ConfigValue("EnchantFormula", "Enchant formula", "This says which formula to use for enchanting (creating enchantment).\n0 = disabled, don't overwrite enchanting XP gain at all.\n1 = vanilla, you get 1 XP for every enchant, this is same as disabled\n2 = reworked \"[((ItemBaseCost + EnchantItemExtraCost) / EnchantItemAverageCost) * ((SoulBaseCost + EnchantSoulExtraCost) / EnchantSoulAverageCost) + EnchantXPFlat] / ((SkillLevel + EnchantXPSkillExtra) * EnchantXPSkillMult + 1)\"\n3 = same as reworked.")]
        public int EnchantFormula
        {
            get;
            set;
        } = 2;
        
        [ConfigValue("EnchantItemExtraCost", "Enchant item extra cost", "Add this amount to enchant item base cost for calculating XP. This is used to reduce the importance of item cost when enchanting.")]
        public float EnchantItemExtraCost
        {
            get;
            set;
        } = 100.0f;

        [ConfigValue("EnchantItemAverageCost", "Enchant item average cost", "Divide the enchanted item base cost by this amount to get the XP multiplier.")]
        public float EnchantItemAverageCost
        {
            get;
            set;
        } = 300.0f;

        [ConfigValue("EnchantSoulExtraCost", "Enchant soul extra cost", "The extra cost to add to all soul gems when calculating XP.")]
        public float EnchantSoulExtraCost
        {
            get;
            set;
        } = 0.0f;

        [ConfigValue("EnchantSoulAverageCost", "Enchant soul average cost", "The average cost of soul gem when calculating XP multiplier.")]
        public float EnchantSoulAverageCost
        {
            get;
            set;
        } = 200.0f;

        [ConfigValue("EnchantXPFlat", "Enchant XP flat", "This is the flat amount component of the enchanting formula.")]
        public float EnchantXPFlat
        {
            get;
            set;
        } = 0.0f;

        [ConfigValue("EnchantXPSkillExtra", "Enchant XP skill extra", "This is the extra skill component of the enchanting formula chosen above. What it does is pretend our enchanting skill is this much higher than it really is. The purpose of this is to make sure we don't get massive amount of experience on level 5 and then suddenly half experience at level 10.")]
        public float EnchantXPSkillExtra
        {
            get;
            set;
        } = 10.0f;

        [ConfigValue("EnchantXPSkillMult", "Enchant XP skill multiplier", "This is the skill multiplier component of the enchanting formula chosen above.")]
        public float EnchantXPSkillMult
        {
            get;
            set;
        } = 0.05f;

        #endregion

        #region Disenchanting

        [ConfigValue("DisenchantFormula", "Disenchant formula", "This says which formula to use for disenchanting (leaning enchantment from destroyed item).\n0 = disabled, don't overwrite disenchanting XP gain at all.\n1 = vanilla, \"DisenchantXPMult * EnchantmentValue\"\n2 = reworked \"[DisenchantXPMult * EnchantmentValue * [(BaseItemGoldValue + DisenchantXPItemExtra) / DisenchantXPItemAverage]] / [(SkillLevel + DisenchantXPSkillExtra) * DisenchantXPSkillMult + 1]\". The BaseItemGoldValue is without the enchantment! This is not what you see in-game.\n3 = same as reworked.")]
        public int DisenchantFormula
        {
            get;
            set;
        } = 2;

        [ConfigValue("DisenchantXPMult", "Disenchant multiplier", "The multiplier in the chosen formula above.")]
        public float DisenchantXPMult
        {
            get;
            set;
        } = 0.0025f;

        [ConfigValue("DisenchantXPItemExtra", "Disenchant item extra cost", "Add this amount to disenchant item base cost for calculating XP. This is used to reduce the importance of item cost when enchanting.")]
        public float DisenchantXPItemExtra
        {
            get;
            set;
        } = 50.0f;

        [ConfigValue("DisenchantXPItemAverage", "Disenchant item average cost", "Divide the disenchanted item base cost by this amount to get the XP multiplier.")]
        public float DisenchantXPItemAverage
        {
            get;
            set;
        } = 300.0f;
        
        [ConfigValue("DisenchantXPSkillExtra", "Disenchant XP skill extra", "This is the extra skill component of the disenchanting formula chosen above. What it does is pretend our enchanting skill is this much higher than it really is. The purpose of this is to make sure we don't get massive amount of experience on level 5 and then suddenly half experience at level 10.")]
        public float DisenchantXPSkillExtra
        {
            get;
            set;
        } = 10.0f;

        [ConfigValue("DisenchantXPSkillMult", "Disenchant XP skill multiplier", "This is the skill multiplier component of the disenchanting formula chosen above.")]
        public float DisenchantXPSkillMult
        {
            get;
            set;
        } = 0.05f;

        #endregion

        #region Alchemy

        [ConfigValue("AlchemyFormula", "Alchemy formula", "This says which formula to use for alchemy (creating potion or poison).\n0 = disabled, don't overwrite alchemy XP gain at all.\n1 = also disabled, same as 0\n2 = reworked \"[AlchemyXPMult * (SumOfIngredientCost ^ AlchemyXPCostExp) * (IngredientCount ^ AlchemyXPExp)] / [(SkillLevel + AlchemyXPSkillExtra) * AlchemyXPSkillMult + 1]\"\n3 = same as reworked.")]
        public int AlchemyFormula
        {
            get;
            set;
        } = 2;

        [ConfigValue("AlchemyXPMult", "Alchemy XP multiplier", "This is the multiplier component of the alchemy formula chosen above.")]
        public float AlchemyXPMult
        {
            get;
            set;
        } = 2.0f;

        [ConfigValue("AlchemyXPCostExp", "Alchemy XP cost exponent", "This is the cost exponent component of the alchemy formula chosen above.")]
        public float AlchemyXPCostExp
        {
            get;
            set;
        } = 1.2f;

        [ConfigValue("AlchemyXPExp", "Alchemy XP exponent", "This is the exponent component of the alchemy formula chosen above.")]
        public float AlchemyXPExp
        {
            get;
            set;
        } = 2.0f;

        [ConfigValue("AlchemyXPSkillExtra", "Alchemy XP skill extra", "This is the extra skill component of the alchemy formula chosen above. What it does is pretend our alchemy skill is this much higher than it really is. The purpose of this is to make sure we don't get massive amount of experience on level 5 and then suddenly half experience at level 10.")]
        public float AlchemyXPSkillExtra
        {
            get;
            set;
        } = 10.0f;

        [ConfigValue("AlchemyXPSkillMult", "Alchemy XP skill multiplier", "This is the skill multiplier component of the alchemy formula chosen above.")]
        public float AlchemyXPSkillMult
        {
            get;
            set;
        } = 0.05f;

        #endregion

        [ConfigValue("DebugMode", "Debug mode", "Is debug mode enabled? If 1 then whenever any hooks are enabled and we replace the XP gained, it will write out to file /Data/NetScriptFramework/Plugins/CraftingSkill.debug.txt the old (original) XP and newly replaced XP. If 2 then it will show the message in HUD instead.")]
        public int DebugMode
        {
            get;
            set;
        } = 0;

        public void Load()
        {
            ConfigFile.LoadFrom(this, "CraftingSkill", true);
        }
    }
}
