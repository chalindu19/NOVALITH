import 'package:firebase_database/firebase_database.dart';
import 'package:novalith/Models/DB/Chat.dart';
import 'package:novalith/Models/DB/LoggedUser.dart';
import 'package:novalith/Models/Utils/FirebaseStructure.dart';
import 'package:novalith/Models/Utils/Utils.dart';

class ChatController {
  late DatabaseReference _databaseReference;

  ChatController() {
    _databaseReference = FirebaseDatabase.instance.ref();
  }

  Future<void> enrollment(context, ChatModel chatModel) async {
    String? key = _databaseReference.child(FirebaseStructure.chats).push().key;
    var _data = {
      'from': chatModel.from,
      'to': chatModel.to,
      'message': chatModel.message,
      'datetime': chatModel.datetime
    };

    await _databaseReference
        .child(FirebaseStructure.users)
        .child(chatModel.from)
        .child(FirebaseStructure.chats)
        .child(chatModel.to)
        .child(key!)
        .set(_data);

    await _databaseReference
        .child(FirebaseStructure.users)
        .child(chatModel.to)
        .child(FirebaseStructure.chats)
        .child(chatModel.from)
        .child(key!)
        .set(_data);
  }
}
