module PhotoModeEx

public func CountFracDigits(x: Float) -> Int32 {
    let s = FloatToString(x);
    let a = StrFindLast(s, ".");

    let b = StrLen(s) - 1;
    while Equals(StrMid(s, b, 1), "0") {
        b -= 1;
    }

    return b - a;
}

public func FormatFloat(x: Float, p: Int32) -> String {
    let s = FloatToStringPrec(x, p);

    if RoundTo(x, 0) == x {
        s += "." + ("0" * p);
    }

    return s;
}
