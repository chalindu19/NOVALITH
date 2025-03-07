import 'dart:convert';

import 'package:flutter/material.dart';
import 'package:intl/intl.dart';
import 'package:novalith/Models/DB/LoggedUser.dart';
import 'package:novalith/Models/Utils/Colors.dart';
import 'package:shared_preferences/shared_preferences.dart';

class CustomUtils{
  static const int DEFAULT_SNACKBAR = 1;
  static const int SUCCESS_SNACKBAR = 2;
  static const int ERROR_SNACKBAR = 3;

  static String? loggedInToken;
  static late LoggedUser? loggedInUser;
  static late String selectedUserForDoctor;

  static SharedPreferences? _prefs;
  static String userAuthToken = 'auth';
  static String disasterTypesToken = 'types';

  static Color getStatusColor(int status) {
    return [color12, color14, color3, color15][status - 1];
  }

  static Widget getEmptyList() {
    return Center(
      child: Text(
        "No Data Found",
        style: TextStyle(fontSize: 15.0, color: colorBlack),
      ),
    );
  }

  static Widget getListLoader() {
    return const Wrap(
      children: [
        Padding(
          padding: EdgeInsets.only(top: 50.0),
          child: CircularProgressIndicator(),
        )
      ],
    );
  }

  static String getCurrentDate() {
    return DateFormat("yyyy/MM/dd").format(DateTime.now());
  }

  static String formatDate(DateTime date) {
    return DateFormat("yyyy/MM/dd").format(date);
  }

  static String formatTime(DateTime date) {
    return DateFormat("hh:mm a").format(date);
  }

  static String formatDateTime(DateTime date) {
    return DateFormat("yyyy/MM/dd hh:mm a").format(date);
  }

  static String getAgeUsingBirthdate(String date) {
    DateTime birthdate = DateFormat("yyyy/MM/dd").parse(date);
    return (DateTime.now().year - birthdate.year).toString();
  }

  static String formatTimeAPI(DateTime date) {
    return DateFormat("hh:mm:ss").format(date);
  }

  static saveAuth(String token) async {
    _prefs ??= await SharedPreferences.getInstance();
    await _prefs!.setString(userAuthToken, token);
    setLoggedToken(token);
  }

  static Future<String?> getAuth() async {
    _prefs ??= await SharedPreferences.getInstance();
    setLoggedToken(_prefs!.getString(userAuthToken));
    return (loggedInToken != null) ? getToken() : loggedInToken;
  }

  static clearToken() async {
    _prefs ??= await SharedPreferences.getInstance();
    _prefs!.remove(userAuthToken);
  }

  static setLoggedToken(token) {
    if (token == null) {
      return;
    }
    loggedInToken = base64.encode(utf8.encode(token));
    return loggedInToken;
  }

  static getToken() {
    return utf8.decode(base64.decode(loggedInToken!));
  }

  static getUser() {
    return loggedInUser;
  }
}