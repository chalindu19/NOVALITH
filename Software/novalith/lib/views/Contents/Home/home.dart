import 'package:flutter/material.dart';
import 'package:intl/intl.dart';
import 'package:novalith/Models/Utils/Colors.dart';
import 'package:novalith/Models/Utils/FirebaseStructure.dart';
import 'package:awesome_notifications/awesome_notifications.dart';
import 'package:firebase_database/firebase_database.dart';

class Home extends StatefulWidget {
  const Home({super.key});

  @override
  State<Home> createState() => _HomeState();
}

class _HomeState extends State<Home> {

  final DatabaseReference _databaseReference = FirebaseDatabase.instance.ref();

  dynamic dataLive;

  @override
  void initState() {
    initNotifications();
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(

    );
  }

  Widget _buildDataCard({
    required IconData icon,
    required String title,
    required String value,
    required String unit,
  }) {
    return Expanded(
      child: Container(
        padding: EdgeInsets.all(16),
        margin: EdgeInsets.symmetric(horizontal: 4),
        decoration: BoxDecoration(
          color: Colors.white,
          //border: Border.all(color: colorPrimary),
          borderRadius: BorderRadius.circular(12),
        ),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Icon(icon, color: Colors.grey[600]),
            SizedBox(height: 8),
            Text(
              title,
              style: TextStyle(fontSize: 16, fontWeight: FontWeight.w500),
            ),
            SizedBox(height: 8),
            Text(
              value,
              style: TextStyle(fontSize: 24, fontWeight: FontWeight.bold),
            ),
            Text(
              unit,
              style: TextStyle(
                  fontSize: 14,
                  color: colorPrimary,
                  fontWeight: FontWeight.bold),
            ),
          ],
        ),
      ),
    );
  }

  String getDateTime(int mills) {
    return DateFormat('yyyy/MM/dd')
        .format(DateTime.fromMillisecondsSinceEpoch(mills));
  }

  int getWeekOfMonth(int mills) {
    return getWeekOfMonthInit(DateTime.fromMillisecondsSinceEpoch(mills));
  }

  int getWeekOfMonthInit(DateTime date) {
    int weekOfMonth = ((date.day + date.weekday - 1) / 7).ceil();
    return weekOfMonth;
  }

  void initNotifications() {
    AwesomeNotifications().isNotificationAllowed().then((isAllowed) {
      if (!isAllowed) {
        AwesomeNotifications().requestPermissionToSendNotifications();
      } else {
        _databaseReference
            .child(FirebaseStructure.notification)
            .onValue
            .listen((DatabaseEvent data) async {
          dynamic noti = data.snapshot.value;
          if (noti['isNew'] == true) {
            AwesomeNotifications().createNotification(
                content: NotificationContent(
                    id: -1,
                    channelKey: 'emergency_traumacare',
                    title: 'Notification',
                    body: noti['message'].toString()));

            await _databaseReference
                .child(FirebaseStructure.notification)
                .child('isNew')
                .set(false);
          }
        });
      }
    });
  }
}