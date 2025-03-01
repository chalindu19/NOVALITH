import 'package:flutter/material.dart';
import 'package:novalith/navigations/aiAgent.dart';
import 'package:novalith/navigations/chat.dart';
import 'package:novalith/navigations/dashboard.dart';
import 'package:novalith/navigations/profile.dart';
import 'package:novalith/navigations/stats.dart';

class Homepage extends StatefulWidget {
  const Homepage({super.key});

  @override
  State<Homepage> createState() => _HomepageState();
}

class _HomepageState extends State<Homepage> {
  var _currentIndex = 0;
  @override
  Widget build(BuildContext context) {
    final List<Widget> pages = [
      const Dashboard(),
      const Profile(),
      const Stats(),
      const Aiagent(),
      const Chat(),
    ];
    return Scaffold(
      bottomNavigationBar: BottomNavigationBar(
        currentIndex: _currentIndex,
        selectedItemColor: Colors.blueAccent,
        unselectedItemColor: Colors.blueGrey,
        onTap: (index) {
          setState(() {
            _currentIndex = index;
          });
        },
        items: const [
          BottomNavigationBarItem(
            icon: Icon(Icons.home),
            label: "Home",
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.person),
            label: "Profile",
          ),
          BottomNavigationBarItem(
            icon: Icon(
              Icons.bar_chart,
              color: Colors.blueAccent,
              size: 65,
            ),
            label: "Stats",
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.panorama_photosphere_outlined),
            label: "Ai Agent",
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.chat),
            label: "Chat",
          ),
        ],
      ),
      body: pages[_currentIndex],
    );
  }
}