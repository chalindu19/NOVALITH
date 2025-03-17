import 'package:firebase_database/firebase_database.dart';
import 'package:novalith/Models/DB/Chat.dart';
import 'package:novalith/Models/DB/LoggedUser.dart';
import 'package:novalith/Models/Utils/FirebaseStructure.dart';
import 'package:novalith/Models/Utils/Utils.dart';

// Controller for handling chat-related operations
class ChatController {
  // Firebase Realtime Database reference
  late DatabaseReference _databaseReference;

  ChatController() {
    _databaseReference = FirebaseDatabase.instance.ref();
  }

  // Saves a chat message in Firebase for both sender and receiver
  Future<void> enrollment(context, ChatModel chatModel) async {
    // Generate a unique key for the chat message
    String? key = _databaseReference.child(FirebaseStructure.chats).push().key;

    // Prepare chat data
    var _data = {
      'from': chatModel.from,
      'to': chatModel.to,
      'message': chatModel.message,
      'datetime': chatModel.datetime
    };

    // Store the message under the sender's chat node
    await _databaseReference
        .child(FirebaseStructure.users)
        .child(chatModel.from)
        .child(FirebaseStructure.chats)
        .child(chatModel.to)
        .child(key!)
        .set(_data);

    // Store the same message under the receiver's chat node
    await _databaseReference
        .child(FirebaseStructure.users)
        .child(chatModel.to)
        .child(FirebaseStructure.chats)
        .child(chatModel.from)
        .child(key!)
        .set(_data);
  }
}
