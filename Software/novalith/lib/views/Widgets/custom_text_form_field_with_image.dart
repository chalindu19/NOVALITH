import 'package:flutter/material.dart';
import 'package:novalith/Models/Utils/Colors.dart';

class CustomTextFieldWithImage extends StatefulWidget {
  // Declare instance variables for customization
  double height = 5.0;
  String hint;
  String icon_img;
  TextInputType textInputType;
  Color backgroundColor;
  bool isIconAvailable;
  var validation;
  bool obscureText;
  TextEditingController controller;

  // Constructor to initialize the widget with required properties
  CustomTextFieldWithImage(
      {Key? key,
      required this.height,
      required this.hint,
      required this.icon_img,
      required this.textInputType,
      required this.backgroundColor,
      required this.isIconAvailable,
      required this.validation,
      required this.controller,
      required this.obscureText})
      : super(key: key);

  @override
  State<CustomTextFieldWithImage> createState() =>
      _CustomTextFieldWithImageState(
          height: height,
          hint: hint,
          icon_img: icon_img,
          textInputType: textInputType,
          backgroundColor: backgroundColor,
          controller: controller,
          isIconAvailable: isIconAvailable,
          validation: validation,
          obscureText: obscureText);
}

class _CustomTextFieldWithImageState extends State<CustomTextFieldWithImage> {
  // Declare instance variable for the state class
  double height = 5.0;
  String hint;
  String icon_img;
  TextInputType textInputType;
  Color backgroundColor;
  bool isIconAvailable;
  var validation;
  bool obscureText;
  TextEditingController controller;

  _CustomTextFieldWithImageState(
      {required this.height,
      required this.hint,
      required this.icon_img,
      required this.textInputType,
      required this.backgroundColor,
      required this.isIconAvailable,
      required this.validation,
      required this.controller,
      required this.obscureText});

  @override
  Widget build(BuildContext context) {
    return Container(
      decoration: BoxDecoration(
          color: backgroundColor, borderRadius: BorderRadius.circular(5.0)),
      padding: EdgeInsets.symmetric(vertical: height, horizontal: 10.0),
      child: Row(
        children: [
          // Display an icon image if available
          (isIconAvailable == true)
              ? Image.asset(
                  icon_img,
                )
              : const SizedBox.shrink(),
          // Flexible TextFormField to handle user input
          Flexible(
              child: TextFormField(
            controller: controller,
            obscureText: obscureText, // Control visibility of input text
            cursorColor: color3, // Define cursor color
            keyboardType: textInputType,
            validator: validation, // Assign validation function
            decoration: InputDecoration(
                hintStyle: TextStyle(color: color8),
                label: Text(hint), // Input label
                labelStyle:
                    TextStyle(color: color8, fontFamily: 'Raleway-SemiBold'),
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
    );
  }
}
