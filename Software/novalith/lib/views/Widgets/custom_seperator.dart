import 'package:flutter/material.dart';

class CustomeSeperator extends StatefulWidget {
  final Color color;
  final double horizontal;

  CustomeSeperator({Key? key, required this.color, required this.horizontal})
      : super(key: key);

  @override
  State<CustomeSeperator> createState() => _CustomeSeperatorState();
}

class _CustomeSeperatorState extends State<CustomeSeperator> {
  @override
  Widget build(BuildContext context) {
    return Container(); // Placeholder for UI
  }
}
