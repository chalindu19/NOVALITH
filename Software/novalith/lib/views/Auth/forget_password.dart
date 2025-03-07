import 'package:flutter/material.dart';
import 'package:form_validation/form_validation.dart';
import 'package:novalith/Controllers/AuthController.dart';
import 'package:novalith/Models/Strings/forget_password.dart';
import 'package:novalith/Models/Strings/register_screen.dart';
import 'package:novalith/Models/Utils/Colors.dart';
import 'package:novalith/Models/Utils/Common.dart';
import 'package:novalith/Models/Utils/Images.dart';
import 'package:novalith/Models/Utils/Routes.dart';
import 'package:novalith/Models/Utils/Utils.dart';
import 'package:novalith/Views/Widgets/custom_button.dart';
import 'package:novalith/Views/Widgets/custom_back_button.dart';
import 'package:novalith/Views/Widgets/custom_text_form_field.dart';



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
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Padding(
                      padding: const EdgeInsets.symmetric(vertical: 20.0),
                      child: CustomCustomBackButton(
                          onclickFunction: () =>
                              Routes(context: context).back())),
                  Padding(
                    padding: EdgeInsets.only(bottom: displaySize.width * 0.3),
                    child: Column(
                      children: [
                        Align(
                            alignment: Alignment.center,
                            child: SizedBox(
                              width: displaySize.width * 0.5,
                              child: Image.asset(passwordReset),
                            )),
                        const SizedBox(
                          height: 30.0,
                        ),
                        Center(
                          child: Text(
                            "Forget Password".toUpperCase(),
                            style: TextStyle(
                                fontSize: 18.0,
                                fontWeight: FontWeight.w500,
                                color: color11),
                          ),
                        ),
                        const SizedBox(
                          height: 10.0,
                        ),
                        Align(
                          alignment: Alignment.center,
                          child: Padding(
                            padding: const EdgeInsets.only(top: 5.0),
                            child: Text(
                              "Reset your account password".toUpperCase(),
                              style: TextStyle(
                                  fontSize: 12.0, color: colorPrimary),
                            ),
                          ),
                        ),
                        SizedBox(
                          height: displaySize.width * 0.1,
                        ),
                        Padding(
                          padding: const EdgeInsets.symmetric(
                              horizontal: 20.0, vertical: 5.0),
                          child: CustomTextFormField(
                              height: 5.0,
                              controller: _email,
                              backgroundColor: color7,
                              iconColor: colorPrimary,
                              isIconAvailable: true,
                              hint: 'Email',
                              icon: Icons.email,
                              textInputType: TextInputType.text,
                              validation: (value) {
                                final validator = Validator(
                                  validators: [const RequiredValidator()],
                                );
                                return validator.validate(
                                  label: register_validation_invalid_email,
                                  value: value,
                                );
                              },
                              obscureText: false),
                        ),
                        Padding(
                          padding: const EdgeInsets.symmetric(
                              horizontal: 45.0, vertical: 5.0),
                          child: CustomButton(
                              buttonText: forget_passsword_button_text,
                              textColor: color6,
                              backgroundColor: colorPrimary,
                              isBorder: false,
                              borderColor: color6,
                              onclickFunction: () async {
                                FocusScope.of(context).unfocus();
                                if (_keyForm.currentState!.validate()) {
                                  CustomUtils.showLoader(context);
                                  await _authController
                                      .sendPasswordResetLink(
                                          context, _email.text)
                                      .then((value) {
                                    // ignore: use_build_context_synchronously
                                    CustomUtils.hideLoader(context);
                                    _email.text = '';
                                    CustomUtils.showSnackBarMessage(
                                        // ignore: use_build_context_synchronously
                                        context,
                                        "Password Reset Link Sent",
                                        CustomUtils.ERROR_SNACKBAR);
                                    // ignore: use_build_context_synchronously
                                    Routes(context: context).back();
                                  });
                                }
                              }),
                        )
                      ],
                    ),
                  )
                ],
              )),
        ),
      )),
    );
  }
}