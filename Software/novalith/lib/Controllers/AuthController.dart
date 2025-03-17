import 'package:firebase_auth/firebase_auth.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:novalith/Models/DB/LoggedUser.dart';
import 'package:novalith/Models/Utils/FirebaseStructure.dart';
import 'package:novalith/Models/Utils/Utils.dart';
import 'package:novalith/Views/Auth/Login.dart';
import 'package:flutter/material.dart';

// Controller for handling authentication-related operations
class AuthController {

  // Firebase Authentication instance
  static late FirebaseAuth _auth;
  // Firebase Realtime Database reference
  late DatabaseReference _databaseRef;

  AuthController() {
    _auth = FirebaseAuth.instance;
    _databaseRef = FirebaseDatabase.instance.ref();
  }

  // Registers a new user with email and password
  Future<bool> doRegistration(data) async {
    bool check = true;

    await _auth
        .createUserWithEmailAndPassword(
      email: data['email'],
      password: data['password'],
    )
        .then((value) async {
      // Remove password before storing user data
      data.remove('password');

      // Save user data in the database
      await _databaseRef
          .child(FirebaseStructure.users)
          .child(value.user!.uid)
          .set(data);

      CustomUtils.showToast('Successfully Registered. Please Login Now.');
    }).catchError((e) {
      check = false;
      CustomUtils.showToast(e.toString());
    });

    return check;
  }

  // Logs in an existing user using email and password
  Future<bool> doLogin(data) async {
    bool check = true;

    await _auth
        .signInWithEmailAndPassword(
      email: data['email'],
      password: data['password'],
    )
        .catchError((e) {
      check = false;
      
      // Error message based on FirebaseAuthException codes
      late String errorMessage;

      switch (e.code) {
        case 'invalid-email':
        case 'user-not-found':
        case 'wrong-password':
          errorMessage = 'Invalid credentails.';
          break;
        case 'user-disabled':
          errorMessage = 'Account has been disabled.';
          break;
        default:
          errorMessage = 'Something wrong.';
      }

      CustomUtils.showToast(errorMessage);
    }).then((value) async {
      // Fetch user data if login is successful
      CustomUtils.loggedInUser = await getUserData();
    });

    return Future.value(check);
  }

  // Logs out the current user and navigates to the login screen
  Future<void> logout(context) async {
    await _auth.signOut();
    Navigator.pushReplacement(
        context, MaterialPageRoute(builder: (_) => const Login()));
  }
  
  // Retrieves user data from Firebase Realtime Database
  Future<LoggedUser> getUserData() async {
    late LoggedUser user;
    await _databaseRef
        .child(FirebaseStructure.users)
        .child(_auth.currentUser!.uid)
        .once()
        .then((DatabaseEvent event) async {
      Map<dynamic, dynamic> profileUserData = event.snapshot.value as Map;
      if (event.snapshot.value != null) {
        user = LoggedUser(
            name: profileUserData['name'],
            address: profileUserData['address'],
            mobile: profileUserData['mobile'],
            email: _auth.currentUser!.email,
            type: profileUserData['type'],
            uid: _auth.currentUser!.uid);
      }
    });

    return user;
  }

  // Checks if a user is logged in
  Future<bool> doLoginCheck() async {
    bool check = false;
    return check;
  }

  // Sends a password reset email to the provided email address
  Future<dynamic> sendPasswordResetLink(context, email) async {
    dynamic check = false;
    _auth.sendPasswordResetEmail(email: email).then((value) => check = true);
    return check;
  }
}