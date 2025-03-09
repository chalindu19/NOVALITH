import 'dart:typed_data';
import 'package:flutter/material.dart';

class CustomImageChooser extends StatelessWidget {
  double height;
  Color backgroundColor;
  String addButtonText;
  List<Uint8List> images;
  int maxImagesCount;
  String? label;
  dynamic onItemRemove;
  dynamic onItemAdded;

  CustomImageChooser({
    super.key,
    this.label,
    required this.onItemRemove,
    required this.onItemAdded,
    required this.maxImagesCount,
    required this.addButtonText,
    required this.height,
    required this.backgroundColor,
    required this.images,
  });

  @override
  Widget build(BuildContext context) {
    return Container(); // Placeholder for UI
  }
}
