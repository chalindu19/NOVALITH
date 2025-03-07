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
  final AuthController _authController = AuthController();
  final _keyForm = GlobalKey<FormState>();

  final TextEditingController _username = TextEditingController();
  final TextEditingController _password = TextEditingController();

  @override
  void initState() {
    _username.text = 'user@gmail.com';
    _password.text = 'User@123';

    // _username.text = 'doctor@gmail.com';
    // _password.text = 'Doctor@123';

    super.initState();
  }

 @override
Widget build(BuildContext context) {
  return Scaffold(
    resizeToAvoidBottomInset: false,
    backgroundColor: color6,
    body: SafeArea(
      child: SizedBox(
        height: displaySize.height,
        width: displaySize.width,
        child: Padding(
          padding: const EdgeInsets.symmetric(horizontal: 10.0),
          child: Form(
            key: _keyForm,
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Align(
                  alignment: Alignment.center,
                  child: SizedBox(
                    width: displaySize.width * 0.4,
                    child: Image.asset(logo),
                  ),
                ),
                const SizedBox(height: 20.0),
                Center(
                  child: Text(
                    Login_title.toUpperCase(),
                    style: TextStyle(
                      fontSize: 22.0,
                      fontWeight: FontWeight.w500,
                      color: color11,
                    ),
                  ),
                ),
                Align(
                  alignment: Alignment.center,
                  child: Padding(
                    padding: const EdgeInsets.only(top: 5.0),
                    child: Text(
                      Login_subtitle.toUpperCase(),
                      style: TextStyle(fontSize: 12.0, color: colorPrimary),
                    ),
                  ),
                ),
                SizedBox(height: displaySize.width * 0.1
                ),
              ],
            ),
          ),
        ),
      ),
    ),
  );
}