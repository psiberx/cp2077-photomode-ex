module PhotoModeEx

@wrapMethod(gameuiPhotoModeMenuController)
protected cb func OnShow(reversedUI: Bool) -> Bool {
    wrappedMethod(reversedUI);

    inkWidgetRef.SetMargin(this.m_menuListRoot, new inkMargin(0.0, 0.0, 109.0, 740.0));
}

@wrapMethod(gameuiPhotoModeMenuController)
public final func SetCurrentMenuPage(page: Uint32) {
    wrappedMethod(page);
    if page == 0u {
        inkTextRef.SetText(this.m_tabTitleText,
            GetLocalizedTextByKey(n"UI-PhotoMode-TabCamera") + " / " +
            GetLocalizedTextByKey(n"UI-Settings-Interface-CameraControls-Title"));
    }
}
