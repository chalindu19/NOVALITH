import 'package:flutter/material.dart';
import 'package:novalith/Models/Utils/Colors.dart';
import 'package:novalith/Models/Utils/Routes.dart';

class History extends StatefulWidget {
  const History({super.key});

  @override
  State<History> createState() => _HistoryState();
}

class _HistoryState extends State<History> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: color7,
      appBar: AppBar(
        backgroundColor: colorPrimary,
        leading: IconButton(
          icon: const Icon(Icons.arrow_back_ios, color: Colors.white),
          onPressed: () {
            Routes(context: context).back();
          },
        ),
        title: const Text("History", style: TextStyle(color: Colors.white)),
        centerTitle: true,
      ),
      body: const Center(child: Text("History Data Will Be Shown Here")),
    );
  }
}
