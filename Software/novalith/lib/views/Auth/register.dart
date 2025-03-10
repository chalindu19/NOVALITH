import 'package:flutter/material.dart';
import 'package:form_validation/form_validation.dart';
import 'package:novalith/Controllers/AuthController.dart';
import 'package:novalith/Models/DB/LoggedUser.dart';
import 'package:novalith/Models/Strings/main_screen.dart';
import 'package:novalith/Models/Utils/Common.dart';
import 'package:novalith/Models/Utils/Utils.dart';
import 'package:novalith/Views/Widgets/custom_button.dart';
import 'package:novalith/Views/Widgets/custom_text_form_field.dart';

import '../../Models/Strings/register_screen.dart';
import '../../Models/Utils/Colors.dart';
import '../../Models/Utils/Routes.dart';
import '../Widgets/custom_back_button.dart';

class BusinessRegister extends StatefulWidget {
  const BusinessRegister({super.key});

  @override
  State<BusinessRegister> createState() => _BusinessRegisterState();
}

class _BusinessRegisterState extends State<BusinessRegister> {
  bool termsAndConditionCheck = false;

  final TextEditingController _name = TextEditingController();
  final TextEditingController _mobile = TextEditingController();
  final TextEditingController _address = TextEditingController();
  final TextEditingController _email = TextEditingController();
  final TextEditingController _password = TextEditingController();
  final TextEditingController _confirm_password = TextEditingController();

  final _formKey = GlobalKey<FormState>();

  final AuthController _authController = AuthController();

  @override
  void initState() {
    _name.text = "";
    _mobile.text = "";
    _address.text = "";
    _email.text = "";
    _password.text = "";
    _confirm_password.text = "";

    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: color6,
      body: SafeArea(
        child: Padding(
          padding: const EdgeInsets.symmetric(horizontal: 10.0),
          child: Column(
            children: [
              CustomTextFormField(
                controller: _name,
                backgroundColor: color7,
                hint: 'Full Name',
                icon: Icons.person_outline,
                textInputType: TextInputType.text,
                obscureText: false,
              ),
              CustomTextFormField(
                controller: _mobile,
                backgroundColor: color7,
                hint: 'Mobile Number',
                icon: Icons.phone_android_outlined,
                textInputType: TextInputType.phone,
                obscureText: false,
              ),
              Padding(
                padding: const EdgeInsets.symmetric(horizontal: 20.0, vertical: 5.0),
                child: CustomTextFormField(
                  height: 5.0,
                  controller: _address,
                  backgroundColor: color7,
                  iconColor: colorPrimary,
                  isIconAvailable: true,
                  hint: 'Address',
                  icon: Icons.map_outlined,
                  maxLines: 3,
                  textInputType: TextInputType.multiline,
                  validation: (value) {
                    final validator = Validator(
                      validators: [const RequiredValidator()],
                    );
                    return validator.validate(
                      label: register_validation_invalid_name,
                      value: value,
                    );                    
                  },
                  obscureText: false,
                ),
              ),
              Padding(
                padding: const EdgeInsets.symmetric(horizontal: 20.0, vertical: 5.0),
                child: CustomTextFormField(
                  height: 5.0,
                  controller: _password,
                  backgroundColor: color7,
                  iconColor: colorPrimary,
                  isIconAvailable: true,
                  hint: 'Password',
                  icon: Icons.lock_open,
                  textInputType: TextInputType.text,
                  validation: (value) {
                    final validator = Validator(
                      validators: [const RequiredValidator()],
                    );
                    return validator.validate(
                      label: register_validation_invalid_password,
                      value: value,
                    );
                  },
                  obscureText: true,
                ),
              ),
              Padding(
                padding: const EdgeInsets.symmetric(horizontal: 20.0, vertical: 5.0),
                child: CustomTextFormField(
                  height: 5.0,
                  controller: _confirm_password,
                  backgroundColor: color7,
                  iconColor: colorPrimary,
                  isIconAvailable: true,
                  hint: 'Confirm Password',
                  icon: Icons.lock_open,
                  textInputType: TextInputType.text,
                  validation: (value) {
                    final validator = Validator(
                      validators: [const RequiredValidator()],
                    );

                    if (value != _password.text) {
                      return register_validation_passwords_does_not_match;
                    }

                    return validator.validate(
                      label: register_validation_invalid_retype_password,
                      value: value,
                    );
                  },
                  obscureText: true,
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
