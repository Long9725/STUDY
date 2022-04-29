void main() {
  RegExp pattern = RegExp('[0-9][.][0-9]');
  /*
  option
  'a'
  */
  print(pattern);
  String str = "Parse my string";
  Iterable<RegExpMatch> matches = pattern.allMatches(str);
  for (var element in matches) {
    print(element.pattern);
    print(element.group(0));
  }
}
