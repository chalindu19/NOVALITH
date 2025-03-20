import 'package:flutter/material.dart';
import 'package:intl/intl.dart';
import 'package:novalith/Models/Strings/app.dart';
import 'package:novalith/Models/Utils/Colors.dart';
import 'package:novalith/Models/Utils/Common.dart';
import 'package:novalith/Models/Utils/FirebaseStructure.dart';
import 'package:awesome_notifications/awesome_notifications.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:novalith/Models/Utils/Utils.dart';
import 'package:novalith/views/Contents/Home/drawer.dart';
import 'package:novalith/views/Widgets/custom_ecg_chart.dart';

class Home extends StatefulWidget {
  const Home({super.key});

  @override
  State<Home> createState() => _HomeState();
}

class _HomeState extends State<Home> {
   final _scaffoldKey = GlobalKey<ScaffoldState>(); // Key for scaffold to control drawer

  final DatabaseReference _databaseReference = FirebaseDatabase.instance.ref(); // Firebase Database reference

  dynamic dataLive; // Store live data from Firebase

  List<ChartData> ecgdata = []; // Store ECG chart data

  @override
  void initState() {
    initNotifications(); // Initialize notifications
    getData(); // Fetch live data
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      key: _scaffoldKey,
        resizeToAvoidBottomInset: false,
        backgroundColor: colorPrimary,
        drawer: HomeDrawer(), // Side navigation drawer
        body: SafeArea(
          child: SizedBox(
              width: displaySize.width,
              height: displaySize.height,
              child: Container(
                color: Colors.grey[100],
                child: Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    // AppBar Section
                    Expanded(
                        flex: 0,
                        child: Container(
                          decoration: BoxDecoration(
                              color: colorPrimary,
                              borderRadius: const BorderRadius.only(
                                  bottomLeft: Radius.circular(10.0),
                                  bottomRight: Radius.circular(10.0))),
                          child: Padding(
                            padding: const EdgeInsets.only(
                                left: 20.0,
                                right: 20.0,
                                top: 18.0,
                                bottom: 18.0),
                            child: Row(
                              mainAxisAlignment: MainAxisAlignment.spaceBetween,
                              crossAxisAlignment: CrossAxisAlignment.center,
                              children: [
                                // Drawer Button
                                GestureDetector(
                                  onTap: () => (_scaffoldKey
                                          .currentState!.isDrawerOpen)
                                      ? _scaffoldKey.currentState!
                                          .openEndDrawer()
                                      : _scaffoldKey.currentState!.openDrawer(),
                                  child: Icon(
                                    Icons.menu_rounded,
                                    color: colorWhite,
                                  ),
                                ),
                                Padding(
                                    padding: const EdgeInsets.symmetric(
                                        vertical: 5.0, horizontal: 15.0),
                                    child: Text(
                                      app_name,
                                      style: TextStyle(
                                          fontSize: 16.0, color: colorWhite),
                                    )),
                                // Refresh Button    
                                GestureDetector(
                                  onTap: () {
                                    getData();
                                  },
                                  child: Icon(
                                    Icons.refresh_rounded,
                                    color: colorWhite,
                                  ),
                                )
                              ],
                            ),
                          ),
                        )),
                    // Main Content Section
                    Expanded(
                        child: SingleChildScrollView(
                      child: Padding(
                        padding: const EdgeInsets.symmetric(
                            vertical: 20.0, horizontal: 10.0),
                        child: (dataLive != null)
                            ? Column(
                                crossAxisAlignment: CrossAxisAlignment.start,
                                children: [
                                  // greeting Text
                                  Text(
                                    'Hello, ${CustomUtils.loggedInUser!.name!}',
                                    style: const TextStyle(
                                        fontSize: 24,
                                        fontWeight: FontWeight.bold),
                                  ),
                                  const SizedBox(height: 8),
                                  Text(
                                    DateFormat('EEEE, MMMM d')
                                        .format(DateTime.now()),
                                    style: const TextStyle(
                                        fontSize: 16, color: Colors.grey),
                                  ),
                                  const SizedBox(height: 24),
                                  // Current Status Card
                                  Container(
                                    padding: const EdgeInsets.all(16),
                                    decoration: BoxDecoration(
                                      color: Colors.white,
                                      borderRadius: BorderRadius.circular(12),
                                    ),
                                    child: Row(
                                      mainAxisAlignment:
                                          MainAxisAlignment.spaceBetween,
                                      children: [
                                        Column(
                                          crossAxisAlignment:
                                              CrossAxisAlignment.start,
                                          children: [
                                            const Text(
                                              'Current Status',
                                              style: TextStyle(
                                                  fontSize: 18,
                                                  fontWeight: FontWeight.w500),
                                            ),
                                            Text(
                                              dataLive['Prediction'],
                                              style: TextStyle(
                                                  fontSize: 20,
                                                  fontWeight: FontWeight.bold,
                                                  color: dataLive['Prediction']
                                                          .toString()
                                                          .toLowerCase()
                                                          .contains('abnormal')
                                                      ? colorRed
                                                      : colorGreen),
                                            ),
                                          ],
                                        ),
                                        Container(
                                          padding: const EdgeInsets.all(8),
                                          decoration: BoxDecoration(
                                            shape: BoxShape.circle,
                                            color: (dataLive['Prediction']
                                                        .toString()
                                                        .toLowerCase()
                                                        .contains('abnormal')
                                                    ? colorRed
                                                    : colorGreen)
                                                .withValues(alpha: 0.2),
                                          ),
                                          child: Icon(Icons.favorite,
                                              color: dataLive['Prediction']
                                                      .toString()
                                                      .toLowerCase()
                                                      .contains('abnormal')
                                                  ? colorRed
                                                  : colorGreen),
                                        ),
                                      ],
                                    ),
                                  ),
                                  const SizedBox(height: 24),
                                  Row(
                                    mainAxisAlignment:
                                        MainAxisAlignment.spaceBetween,
                                    children: [
                                      // Health Data Cards 
                                      _buildDataCard(
                                        icon: Icons.favorite_border,
                                        title: 'Fetal Heart Rate',
                                        value: dataLive['ecg'],
                                        unit: 'BPM',
                                      ),
                                      _buildDataCard(
                                        icon: Icons.directions_run,
                                        title: 'Fetal Movement',
                                        value: dataLive['kicks_count'],
                                        unit: 'movements/hr',
                                      ),
                                    ],
                                  ),
                                  const SizedBox(height: 16),
                                  Row(
                                    mainAxisAlignment:
                                        MainAxisAlignment.spaceBetween,
                                    children: [
                                      _buildDataCard(
                                        icon: Icons.favorite_border,
                                        title: 'Maternal HR',
                                        value: dataLive['heart_rate'],
                                        unit: 'BPM',
                                      ),
                                      _buildDataCard(
                                        icon: Icons.wb_sunny,
                                        title: 'Temperature',
                                        value: dataLive['body_temp'],
                                        unit: '°C',
                                      ),
                                    ],
                                  ),
                                  if (ecgdata.isNotEmpty) const SizedBox(height: 16),
                                  if (ecgdata.isNotEmpty) getECGDataWidget(),
                                  const SizedBox(height: 16),
                                  Row(
                                    mainAxisAlignment:
                                        MainAxisAlignment.spaceBetween,
                                    children: [
                                      _buildDataCard(
                                        icon: Icons.water_drop_outlined,
                                        title: 'Blood Pressure',
                                        value: dataLive['blood_pressure'],
                                        unit: 'mmHg',
                                      )
                                    ],
                                  ),
                                  const SizedBox(height: 16),
                                  Row(
                                    mainAxisAlignment:
                                        MainAxisAlignment.spaceBetween,
                                    children: [
                                      _buildDataCard(
                                        icon: Icons.line_weight_outlined,
                                        title: 'Pressure 1',
                                        value: dataLive['pressure1'],
                                        unit: '%',
                                      ),
                                      _buildDataCard(
                                        icon: Icons.line_weight_outlined,
                                        title: 'Pressure 2',
                                        value: dataLive['pressure2'],
                                        unit: '%',
                                      ),
                                    ],
                                  ),
                                  const SizedBox(height: 16),
                                  Row(
                                    mainAxisAlignment:
                                        MainAxisAlignment.spaceBetween,
                                    children: [
                                      _buildDataCard(
                                        icon: Icons.line_weight_outlined,
                                        title: 'Pressure 3',
                                        value: dataLive['pressure3'],
                                        unit: '%',
                                      ),
                                      _buildDataCard(
                                        icon: Icons.line_weight_outlined,
                                        title: 'Pressure 4',
                                        value: dataLive['pressure4'],
                                        unit: '%',
                                      ),
                                    ],
                                  ),
                                ],
                              )
                            : const SizedBox.shrink(),
                      ),
                    ))
                  ],
                ),
              )),
        ));
  }

  Widget _buildDataCard({
    required IconData icon,
    required String title,
    required String value,
    required String unit,
  }) {
    return Expanded(
      child: Container(
        padding: const EdgeInsets.all(16),
        margin: const EdgeInsets.symmetric(horizontal: 4),
        decoration: BoxDecoration(
          color: Colors.white,
          //border: Border.all(color: colorPrimary),
          borderRadius: BorderRadius.circular(12),
        ),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Icon(icon, color: Colors.grey[600]),
            const SizedBox(height: 8),
            Text(
              title,
              style: const TextStyle(fontSize: 16, fontWeight: FontWeight.w500),
            ),
            const SizedBox(height: 8),
            Text(
              value,
              style: const TextStyle(fontSize: 24, fontWeight: FontWeight.bold),
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

  // Initialize and listen for notifications
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

  // Fetch real-time data from Firebase
  Future<void> getData() async {
    _databaseReference
        .child(FirebaseStructure.livedata)
        .onValue
        .listen((DatabaseEvent data) async {
      setState(() {
        dataLive = data.snapshot.value;

        if (dataLive != null) {
          ecgdata.add(ChartData(ecgdata.length.toDouble(),
              double.parse(dataLive['ecg_read'].toString())));
        }
      });
    });
  }

  getECGDataWidget() {
    return ECGChart(chartData: ecgdata);
  }
}