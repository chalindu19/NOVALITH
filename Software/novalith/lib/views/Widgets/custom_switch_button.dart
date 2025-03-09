import 'package:flutter/cupertino.dart';
import 'package:novalith/Models/Utils/Colors.dart';

class CustomSwitchButton extends StatelessWidget {
  Function(bool)? onChanged;
  bool switchValue;

  CustomSwitchButton({Key? key, this.onChanged, this.switchValue = false})
      : super(key: key);

  @override
  Widget build(BuildContext context) {
    return CupertinoSwitch(
      value: switchValue,
      activeColor: colorPrimary,
      onChanged: onChanged,
    );
  }
}
