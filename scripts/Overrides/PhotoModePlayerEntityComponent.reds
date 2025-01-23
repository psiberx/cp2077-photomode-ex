module PhotoModeEx

@wrapMethod(PhotoModePlayerEntityComponent)
private final func FindMatchingEquipmentInEquipArea(area: gamedataEquipmentArea, typesList: array<gamedataItemType>) -> ItemID {
    if !this.customizable && Equals(area, gamedataEquipmentArea.WeaponWheel) {
        let allItems: array<wref<gameItemData>>;
        let transactionSystem = GameInstance.GetTransactionSystem(this.mainPuppet.GetGame());
        transactionSystem.GetItemList(this.mainPuppet, allItems);

        let i = 0;
        while i < ArraySize(allItems) {
            let itemID = allItems[i].GetID();
            if ItemID.IsValid(itemID) && this.IsItemOfThisType(itemID, typesList) {
                return itemID;
            }
            i += 1;
        }
    }

    return wrappedMethod(area, typesList);
}
