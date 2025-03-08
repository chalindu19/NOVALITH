import 'package:flutter/material.dart';
import 'package:syncfusion_flutter_charts/charts.dart';

class ECGChart extends StatefulWidget {
  final List<ChartData> chartData;

  ECGChart({required this.chartData});

  @override
  _ECGChartState createState() => _ECGChartState();
}

class _ECGChartState extends State<ECGChart> {
  @override
  void initState() {
    super.initState();
  }
}
