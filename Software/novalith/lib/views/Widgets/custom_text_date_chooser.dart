import 'package:flutter/material.dart';
import 'package:flutter_datetime_picker_plus/flutter_datetime_picker_plus.dart';
import 'package:novalith/Models/Utils/Colors.dart';
import 'package:novalith/Models/Utils/Utils.dart';

// A custom text field widget for selecting a date
class CustomTextDateChooser extends StatelessWidget {
  // UI properties
  double height = 5.0;
  String hint;
  IconData icon;
  TextInputType textInputType;
  Color backgroundColor;
  Color iconColor;
  bool isIconAvailable;
  var validation;
  bool obscureText;
  TextEditingController controller;
  var label;

  CustomTextDateChooser(
      {Key? key,
      required this.height,
      required this.hint,
      required this.icon,
      required this.textInputType,
      required this.backgroundColor,
      required this.iconColor,
      required this.isIconAvailable,
      required this.validation,
      this.label,
      required this.controller,
      required this.obscureText})
      : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Wrap(
      children: [
        // Display label if provided
        (label != null)
            ? Padding(
                padding: const EdgeInsets.only(bottom: 5.0),
                child: Text(
                  label,
                  style: TextStyle(
                      fontSize: 14.0,
                      fontWeight: FontWeight.w500,
                      color: color11),
                ),
              )
            : const SizedBox.shrink(),

        // Container for the text field
        Container(
          decoration: BoxDecoration(
              color: backgroundColor, borderRadius: BorderRadius.circular(5.0)),
          padding: EdgeInsets.symmetric(vertical: height, horizontal: 10.0),
          child: Row(
            children: [
              // Display icon if available
              (isIconAvailable == true)
                  ? Icon(
                      icon,
                      color: iconColor,
                    )
                  : const SizedBox.shrink(),
              
              // Date picker text field
              Flexible(
                  child: TextFormField(
                onTap: () async {
                  DateTime date = DateTime(1900);
                  FocusScope.of(context).requestFocus(FocusNode()); // Remove focus from the field

                  // Show date picker dialog
                  DatePicker.showDatePicker(context,
                      showTitleActions: true,
                      maxTime: DateTime.now(), onChanged: (DateTime date) {
                    // Update text field with selected date
                    controller.text = CustomUtils.formatDate(date);
                  }, onConfirm: (date) {
                    controller.text = CustomUtils.formatDate(date);
                  }, currentTime: DateTime.now(), locale: LocaleType.en);
                },
                controller: controller,
                obscureText: obscureText,
                cursorColor: colorPrimary,
                keyboardType: textInputType,
                validator: validation,
                minLines: 1,
                maxLines: 3,
                decoration: InputDecoration(
                    hintStyle: TextStyle(color: color8),
                    label: Text(hint),
                    labelStyle: TextStyle(
                        color: color8, fontFamily: 'Raleway-SemiBold'),
                    border: InputBorder.none,
                    focusedBorder: InputBorder.none,
                    enabledBorder: InputBorder.none,
                    errorBorder: InputBorder.none,
                    disabledBorder: InputBorder.none,
                    contentPadding: const EdgeInsets.only(
                        left: 15, bottom: 11, top: 11, right: 15)),
              ))
            ],
          ),
        )
      ],
    );
  }
}
