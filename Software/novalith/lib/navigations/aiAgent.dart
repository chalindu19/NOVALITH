import 'package:flutter/material.dart';

class Aiagent extends StatefulWidget {
  const Aiagent({super.key});

  @override
  State<Aiagent> createState() => _AiagentState();
}

class _AiagentState extends State<Aiagent> {
  @override
  Widget build(BuildContext context) {
    return const Scaffold(
      body: Center(
        child: Text("Ai"),
      ),
    );
  }
}