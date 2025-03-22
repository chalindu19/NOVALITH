import 'package:flutter/material.dart';

class Profile extends StatelessWidget {
  // Sample user data
  final String profileImageUrl = 'https://example.com/profile.jpg';
  final String name = 'John Doe';
  final String email = 'john.doe@example.com';
  final String phone = '+1 234 567 890';
  final String address = '123 Main Street, City, Country';

  const Profile({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Profile'),
        centerTitle: true,
      ),
      body: SingleChildScrollView(
        child: Column(
          children: [
            // Profile Image
            Container(
              margin: const EdgeInsets.only(top: 20),
              child: CircleAvatar(
                radius: 80,
                backgroundImage: NetworkImage(profileImageUrl),
              ),
            ),
            const SizedBox(height: 20),
            // User Information
            ListTile(
              leading: const Icon(Icons.person),
              title: const Text('Name'),
              subtitle: Text(name),
            ),
            ListTile(
              leading: const Icon(Icons.email),
              title: const Text('Email'),
              subtitle: Text(email),
            ),
            ListTile(
              leading: const Icon(Icons.phone),
              title: const Text('Phone'),
              subtitle: Text(phone),
            ),
            ListTile(
              leading: const Icon(Icons.location_on),
              title: const Text('Address'),
              subtitle: Text(address),
            ),
            const SizedBox(height: 20),
            // Edit Profile Button
            ElevatedButton(
              onPressed: () {
                // Navigate to edit profile page
              },
              child: const Text('Edit Profile'),
            ),
          ],
        ),
      ),
    );
  }
}