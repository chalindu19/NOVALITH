import 'dart:typed_data';

import 'package:flutter/material.dart';
import 'package:novalith/Models/Utils/Colors.dart';
import 'package:novalith/Models/Utils/Common.dart';
import 'package:novalith/Views/Widgets/custom_button.dart';

// ignore: must_be_immutable
class CustomImageChooser extends StatelessWidget {
  double height = 5.0;
  Color backgroundColor;
  String addButtonText;
  List<Uint8List> images;
  int maxImagesCount;
  String? label;
  dynamic onItemRemove;
  dynamic onItemAdded;

  CustomImageChooser(
      {super.key,
      this.label,
      required this.onItemRemove,
      required this.onItemAdded,
      required this.maxImagesCount,
      required this.addButtonText,
      required this.height,
      required this.backgroundColor,
      required this.images});

  @override
  Widget build(BuildContext context) {
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        (label != null)
            ? Padding(
                padding: const EdgeInsets.only(bottom: 5.0),
                child: Text(
                  label!,
                  style: TextStyle(
                      fontSize: 14.0,
                      fontWeight: FontWeight.w500,
                      color: color11),
                ),
              )
            : const SizedBox.shrink(),
        Container(
            decoration: BoxDecoration(
                color: backgroundColor,
                borderRadius: BorderRadius.circular(5.0)),
            padding: EdgeInsets.symmetric(vertical: height),
            child: Column(
              mainAxisSize: MainAxisSize.min,
              children: getContents(context),
            ))
      ],
    );
  }
}
