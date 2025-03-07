import 'package:flutter/material.dart';
import 'package:novalith/Models/Utils/Colors.dart';

class CustomDropDown extends StatelessWidget {
  String dropdown_value;
  String leading_image;
  var leading_icon;
  var leading_icon_color;
  Color action_icon_color;
  Color text_color;
  Color background_color;
  Color underline_color;
  var function;
  var items;
  var label = null;

  CustomDropDown({
    required this.dropdown_value,
    this.label,
    this.leading_image = '',
    this.leading_icon,
    this.leading_icon_color,
    required this.action_icon_color,
    required this.text_color,
    required this.background_color,
    required this.underline_color,
    required this.function,
    required this.items,
  });
}
