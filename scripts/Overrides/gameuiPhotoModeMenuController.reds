module PhotoModeEx

@wrapMethod(gameuiPhotoModeMenuController)
public final func SetCurrentMenuPage(page: Uint32) {
    wrappedMethod(page);
    if page == 0u {
        inkTextRef.SetText(this.m_tabTitleText,
            GetLocalizedTextByKey(n"UI-PhotoMode-TabCamera") + " / " +
            GetLocalizedTextByKey(n"UI-Settings-Interface-CameraControls-Title"));
    }
}
