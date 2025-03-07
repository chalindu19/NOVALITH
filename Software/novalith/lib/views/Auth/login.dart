import 'package:flutter/material.dart';
import 'package:form_validation/form_validation.dart';
import 'package:novalith/Controllers/AuthController.dart';
import 'package:novalith/Models/Strings/login_screen.dart';
import 'package:novalith/Models/Strings/register_screen.dart';
import 'package:novalith/Models/Utils/Colors.dart';
import 'package:novalith/Models/Utils/Common.dart';
import 'package:novalith/Models/Utils/Images.dart';
import 'package:novalith/Models/Utils/Routes.dart';
import 'package:novalith/Models/Utils/Utils.dart';
import 'package:novalith/Views/Auth/forget_password.dart';
import 'package:novalith/Views/Auth/register.dart';
import 'package:novalith/Views/Contents/Home/home.dart';
import 'package:novalith/Views/Widgets/custom_button.dart';
import 'package:novalith/Views/Widgets/custom_text_form_field.dart';


class Login extends StatefulWidget {
  const Login({super.key});

  @override
  State<Login> createState() => _LoginState();
}

class _LoginState extends State<Login> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: Text("Login Screen"),
      ),
    );
  }
}
