import 'dart:async';

import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:form_validation/form_validation.dart';
import 'package:google_fonts/google_fonts.dart';
import 'package:intl/intl.dart';
import 'package:novalith/Controllers/ChatController.dart';
import 'package:novalith/Models/DB/Chat.dart';
import 'package:novalith/Models/Strings/register_screen.dart';
import 'package:novalith/Models/Utils/Colors.dart';
import 'package:novalith/Models/Utils/Common.dart';
import 'package:novalith/Models/Utils/FirebaseStructure.dart';
import 'package:novalith/Models/Utils/Routes.dart';
import 'package:novalith/Models/Utils/Utils.dart';
import 'package:novalith/Views/Widgets/custom_text_area.dart';

class Chat extends StatefulWidget {
  final String selectedUser;

  const Chat({super.key, required this.selectedUser});

  @override
  State<Chat> createState() => _ChatState();
}

class _ChatState extends State<Chat> {
  final double topSpace = displaySize.width * 0.4;

  bool isLoading = true;

  final TextEditingController _messageController = TextEditingController();

  FocusNode focusNode = FocusNode();
  ScrollController scrollController = ScrollController();

  List<Widget> chatList = [];

  final ChatController _chatController = ChatController();

  _ChatState();

  final DatabaseReference _databaseReference = FirebaseDatabase.instance.ref();

  StreamSubscription<DatabaseEvent>? listener;

  @override
  void initState() {
    super.initState();
    refreshChat();
  }

  @override
  void dispose() {
    if (listener != null) {
      listener!.cancel();
    }
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        resizeToAvoidBottomInset: true,
        backgroundColor: colorPrimary,
        body: SafeArea(
          child: SizedBox(
              width: displaySize.width,
              height: displaySize.height,
              child: Container(
                color: colorWhite,
                child: Column(
                  children: [
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
                                GestureDetector(
                                  onTap: () {
                                    Routes(context: context).back();
                                  },
                                  child: Icon(
                                    Icons.arrow_back_ios,
                                    color: colorWhite,
                                  ),
                                ),
                                Text(
                                  "Chat",
                                  style:
                                      TextStyle(fontSize: 16.0, color: color7),
                                ),
                                GestureDetector(
                                  onTap: () async {
                                    setState(() {
                                      _messageController.clear();
                                    });
                                  },
                                  child: Icon(
                                    Icons.refresh_outlined,
                                    color: colorWhite,
                                  ),
                                ),
                              ],
                            ),
                          ),
                        )),
                    Expanded(
                        flex: 1,
                        child: SingleChildScrollView(
                          reverse: (chatList.isNotEmpty) ? true : false,
                          controller: scrollController,
                          child: Column(
                            crossAxisAlignment: (chatList.isNotEmpty)
                                ? CrossAxisAlignment.stretch
                                : CrossAxisAlignment.center,
                            children: (chatList.isNotEmpty)
                                ? chatList
                                : [
                                    Padding(
                                      padding: const EdgeInsets.only(top: 20.0),
                                      child: Text(
                                        'Start chat with administrator',
                                        style: GoogleFonts.openSans(
                                            fontSize: 14.0, color: colorGrey),
                                      ),
                                    )
                                  ],
                          ),
                        )),
                    Expanded(
                        flex: 0,
                        child: Padding(
                          padding: const EdgeInsets.only(top: 20.0),
                          child: Row(
                            children: [
                              Expanded(
                                  flex: 1,
                                  child: Padding(
                                    padding: const EdgeInsets.symmetric(
                                        horizontal: 20.0, vertical: 5.0),
                                    child: CustomTextAreaFormField(
                                        height: 5.0,
                                        controller: _messageController,
                                        backgroundColor: color7,
                                        iconColor: colorPrimary,
                                        isIconAvailable: true,
                                        hint: 'Your message',
                                        icon: Icons.message_outlined,
                                        textInputType: TextInputType.multiline,
                                        validation: (value) {
                                          final validator = Validator(
                                            validators: [
                                              const RequiredValidator()
                                            ],
                                          );
                                          return validator.validate(
                                            label:
                                                register_validation_invalid_message,
                                            value: value,
                                          );
                                        },
                                        obscureText: false),
                                  )),
                              Expanded(
                                  flex: 0,
                                  child: GestureDetector(
                                    onTap: () async {
                                      if (_messageController.text.isNotEmpty) {
                                        ChatModel chatModel = ChatModel(
                                            id: 1,
                                            from: CustomUtils.loggedInUser!.uid,
                                            to: widget.selectedUser,
                                            message: _messageController.text,
                                            datetime: DateTime.now()
                                                .millisecondsSinceEpoch);
                                        _messageController.text = "";
                                        await _chatController.enrollment(
                                            context, chatModel);
                                      }
                                    },
                                    child: Padding(
                                      padding:
                                          const EdgeInsets.only(right: 15.0),
                                      child: Icon(
                                        Icons.send,
                                        color: colorPrimary,
                                      ),
                                    ),
                                  ))
                            ],
                          ),
                        ))
                  ],
                ),
              )),
        ));
  }

  Widget getMessageBubble(ChatModel chatRecord) {
    print(chatRecord.from);

    return Align(
      alignment: (CustomUtils.loggedInUser!.uid == chatRecord.from)
          ? Alignment.centerRight
          : Alignment.centerLeft,
      child: Wrap(
        children: [
          Container(
              constraints: BoxConstraints(maxWidth: displaySize.width * 0.8),
              margin: const EdgeInsets.only(bottom: 5.0),
              decoration: BoxDecoration(
                  borderRadius: BorderRadius.circular(10.0),
                  color: (CustomUtils.loggedInUser!.uid == chatRecord.from)
                      ? colorPrimary
                      : colorSecondary),
              padding:
                  const EdgeInsets.symmetric(vertical: 5.0, horizontal: 20.0),
              child: Column(
                crossAxisAlignment:
                    (chatRecord.from == CustomUtils.loggedInUser!.uid)
                        ? CrossAxisAlignment.end
                        : CrossAxisAlignment.start,
                children: [
                  Text(
                    chatRecord.message ?? "",
                    style:
                        GoogleFonts.openSans(fontSize: 14.0, color: colorWhite),
                  ),
                  if (chatRecord.datetime != null)
                    Padding(
                      padding: const EdgeInsets.only(top: 5.0),
                      child: Text(
                        getDateTime(DateTime.fromMillisecondsSinceEpoch(
                            chatRecord.datetime)),
                        style: GoogleFonts.openSans(
                            fontSize: 10.0, color: colorWhite),
                      ),
                    )
                ],
              ))
        ],
      ),
    );
  }

  getDateTime(DateTime dateTime) {
    return DateFormat('yyyy-MM-dd HH:mm:ss').format(dateTime);
  }

  refreshChat() async {
    if (scrollController.hasClients) {
      scrollController.animateTo(scrollController.position.minScrollExtent,
          duration: const Duration(milliseconds: 100), curve: Curves.ease);
    } else {
      listener = _databaseReference
          .child(FirebaseStructure.users)
          .child(CustomUtils.loggedInUser!.uid!)
          .child(FirebaseStructure.chats)
          .child(widget.selectedUser)
          .onValue
          .listen((event) {
        chatList.clear();

        if (mounted) {
          setState(() {
            for (DataSnapshot element in event.snapshot.children) {
              Map data = element.value as Map;
              chatList.add(getMessageBubble(ChatModel(
                  id: element.key,
                  datetime: data['datetime'],
                  from: data['from'],
                  to: data['to'],
                  message: data['message'])));
            }
          });
        }
      });
    }
  }
}
