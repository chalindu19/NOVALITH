class LoggedUser {
  static int doctor = 1;
  static int user = 2;

  final String? uid, name, email, address, mobile;
  final int type;

  LoggedUser(
      {this.uid,
      this.name,
      this.email,
      this.address,
      this.mobile,
      this.type = 2});
}
