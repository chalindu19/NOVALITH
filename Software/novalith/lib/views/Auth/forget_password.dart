import 'package:flutter/material.dart';




class ForgetPassword extends StatefulWidget {
  const ForgetPassword({super.key});

  @override
  State<ForgetPassword> createState() => _LoginState();
}

class _LoginState extends State<ForgetPassword> {
  final AuthController _authController = AuthController();
  final _keyForm = GlobalKey<FormState>();
  final TextEditingController _email = TextEditingController();

  dynamic response;

  @override
  void initState() {
    super.initState();
  }