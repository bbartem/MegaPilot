class Variant {
public:
  Variant() : isString_(false), isBool_(false) {}

  Variant(const String& str) : isString_(true), isBool_(false), stringValue_(str) {}

  Variant(bool value) : isString_(false), isBool_(true), boolValue_(value) {}

  bool isString() const { return isString_; }
  bool isBool() const { return isBool_; }

  String getString() const {
    if (isString_) {
      return stringValue_;
    } else {
      return String();
    }
  }

  bool getBool() const {
    if (isBool_) {
      return boolValue_;
    } else {
      return false; // or some default value
    }
  }

private:
  bool isString_;
  bool isBool_;
  String stringValue_;
  bool boolValue_;
};
