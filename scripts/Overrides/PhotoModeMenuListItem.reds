import PhotoModeEx.*

@addField(PhotoModeMenuListItem)
private let m_scrollBarFracDigits: Int32;

@wrapMethod(PhotoModeMenuListItem)
protected cb func OnScrollBarValueChanged(controller: wref<inkSliderController>, progress: Float, newValue: Float) -> Bool {
    if this.m_SliderDisplayType == 0u && this.m_scrollBarFracDigits != 0 {
        this.m_SliderValue = newValue;

        inkTextRef.SetText(this.m_CounterLabelRef, FormatFloat(this.m_SliderValue, this.m_scrollBarFracDigits));

        let data = this.GetData() as PhotoModeMenuListItemData;
        this.m_photoModeController.OnAttributeUpdated(data.attributeKey, this.m_SliderValue, this.m_doApply);
        this.m_photoModeController.m_anyOptionChanged = true;
    } else {
        wrappedMethod(controller, progress, newValue);
    }
}

@wrapMethod(PhotoModeMenuListItem)
public final func SetupScrollBar(startValue: Float, minValue: Float, maxValue: Float, step: Float, displayType: Uint32) {
    wrappedMethod(startValue, minValue, maxValue, step, displayType);

    if this.m_SliderDisplayType == 0u && step < 1.0 {
        this.m_scrollBarFracDigits = CountFracDigits(step);

        let extraDigits = Clamp(this.m_scrollBarFracDigits - 2, 0, 3);
        let handleRoot = inkWidgetRef.Get(this.m_ScrollBarHandleRef).parentWidget;
        handleRoot.SetWidth(120.0 + (24.0 * Cast<Float>(extraDigits)));

        this.OnScrollBarValueChanged(null, 0, 0);
    } else {
        this.m_scrollBarFracDigits = 0;
    }
}
