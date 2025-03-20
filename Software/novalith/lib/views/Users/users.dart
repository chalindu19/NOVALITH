import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';
import 'package:intl/intl.dart';
import 'package:novalith/Models/DB/LoggedUser.dart';
import 'package:novalith/Models/Utils/Colors.dart';
import 'package:novalith/Models/Utils/Common.dart';
import 'package:novalith/Models/Utils/FirebaseStructure.dart';
import 'package:novalith/Models/Utils/Routes.dart';
import 'package:novalith/Models/Utils/Utils.dart';
import 'package:novalith/Views/Chat/chat.dart';

class Users extends StatefulWidget {
  const Users({Key? key}) : super(key: key);

  @override
  _UsersState createState() => _UsersState();
}

class _UsersState extends State<Users> {
  // Global key for the scaffold
  final _scaffoldKey = GlobalKey<ScaffoldState>();

  final double topSpace = displaySize.width * 0.4;

  // Database reference for Firebase
  final DatabaseReference _databaseReference = FirebaseDatabase.instance.ref();
  
  // List to store user data.
  List<dynamic> list = [];

  @override
  void initState() {
    getData(); // Fetch user data on initialization
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return SafeArea(
        child: Scaffold(
      key: _scaffoldKey,
      backgroundColor: colorWhite,
      body: SizedBox(
          width: displaySize.width,
          height: displaySize.height,
          child: Column(
            children: [
              Expanded(
                  flex: 0,
                  child: Container(
                    decoration: BoxDecoration(color: colorPrimary),
                    child: Padding(
                      padding: const EdgeInsets.only(
                          left: 20.0, right: 20.0, top: 18.0, bottom: 18.0),
                      child: Row(
                        mainAxisAlignment: MainAxisAlignment.spaceBetween,
                        crossAxisAlignment: CrossAxisAlignment.center,
                        children: [
                          GestureDetector(
                            onTap: () {
                              Navigator.pop(context);
                            },
                            child: Icon(
                              Icons.arrow_back_ios,
                              color: colorWhite,
                            ),
                          ),
                          // Title based on the logged-in user's type.
                          Text(
                            CustomUtils.loggedInUser!.type == LoggedUser.doctor
                                ? 'Patients'
                                : 'Doctors',
                            style: GoogleFonts.nunitoSans(
                                fontSize: 18.0, color: colorWhite),
                          ),
                          GestureDetector(
                            onTap: () => getData().then((value) =>
                                CustomUtils.showSnackBar(
                                    context,
                                    "Refreshing list",
                                    CustomUtils.DEFAULT_SNACKBAR)),
                            child: Icon(
                              Icons.refresh_outlined,
                              color: colorWhite,
                            ),
                          ),
                        ],
                      ),
                    ),
                  )),
              const SizedBox(
                height: 5.0,
              ),
              // User list section.
              Expanded(
                  flex: 1,
                  child: Container(
                    width: double.infinity,
                    decoration: BoxDecoration(
                        color: colorWhite,
                        borderRadius: const BorderRadius.only(
                            topLeft: Radius.circular(30.0),
                            topRight: Radius.circular(30.0))),
                    child: Padding(
                      padding: const EdgeInsets.all(5.0),
                      child: SingleChildScrollView(
                        child: Column(
                            crossAxisAlignment: CrossAxisAlignment.center,
                            children: [
                              // Loop through the user list and create cards
                              for (var rec in list)
                                Card(
                                    shape: RoundedRectangleBorder(
                                      borderRadius: BorderRadius.circular(10),
                                    ),
                                    elevation: 5,
                                    margin: EdgeInsets.symmetric(
                                        vertical: 8, horizontal: 5),
                                    child: Container(
                                        decoration: BoxDecoration(
                                          border: Border.all(
                                            color:
                                                colorSecondary, // Border color
                                            width: 1.5, // Border width
                                          ),
                                          borderRadius:
                                              BorderRadius.circular(10),
                                        ),
                                        child: ListTile(
                                            leading: Container(
                                              decoration: BoxDecoration(
                                                  color: colorPrimary,
                                                  borderRadius:
                                                      BorderRadius.circular(
                                                          100.0)),
                                              child: Padding(
                                                padding: EdgeInsets.all(5.0),
                                                child: Icon(
                                                  Icons.person_2_outlined,
                                                  color: colorWhite,
                                                  size: 25.0,
                                                ),
                                              ),
                                            ),
                                            title: Text(
                                              rec['value']['name'],
                                              style: TextStyle(
                                                  color: colorBlack,
                                                  fontWeight: FontWeight.w400,
                                                  fontSize: 15.0),
                                            ),
                                            subtitle: Text(
                                              rec['value']['email'],
                                              style: GoogleFonts.nunitoSans(
                                                  color: colorBlack,
                                                  fontSize: 12.0),
                                            ),
                                            trailing: PopupMenuButton<String>(
                                              onSelected: (value) {
                                                print("Selected: $value");
                                              },
                                              itemBuilder:
                                                  (BuildContext context) {
                                                return [
                                                  PopupMenuItem(
                                                    value: "Chat",
                                                    child: Text("Chat"),
                                                    onTap: () =>
                                                        Routes(context: context)
                                                            .navigate(Chat(
                                                      selectedUser: rec['key'],
                                                    )),
                                                  ),
                                                ];
                                              },
                                            ))))
                            ]),
                      ),
                    ),
                  ))
            ],
          )),
    ));
  }
  // Fetches user data from Firebase based on the logged-in user's type 
  Future<void> getData() async {
    _databaseReference
        .child(FirebaseStructure.users)
        .orderByChild("type")
        .equalTo(CustomUtils.loggedInUser!.type == LoggedUser.doctor
            ? LoggedUser.user
            : LoggedUser.doctor)
        .once()
        .then((DatabaseEvent data) {
      list.clear();
      for (DataSnapshot element in data.snapshot.children) {
        list.add({'key': element.key, 'value': element.value});
      }
      setState(() {});
    });
  }
  // Formats a timestamp into a readable date and time string
  String getDateTime(int mills) {
    return DateFormat('yyyy/MM/dd hh:mm a')
        .format(DateTime.fromMillisecondsSinceEpoch(mills));
  }
}
