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

 @override
  Widget build(BuildContext context) {
    return SfCartesianChart(
      title: ChartTitle(text: 'ECG Graph'),
      primaryXAxis: NumericAxis(
        majorGridLines: MajorGridLines(width: 0), // Hide X-axis grid lines
      ),
      primaryYAxis: NumericAxis(
        majorGridLines: MajorGridLines(width: 0), // Hide Y-axis grid lines
      ),
      series: <CartesianSeries<ChartData, double>>[
        // Renders line chart
        LineSeries<ChartData, double>(
          dataSource: widget.chartData,
          xValueMapper: (ChartData data, _) => data.x,
          yValueMapper: (ChartData data, _) => data.y,
          color: Colors.red,
          width: 2,
        ),
      ],
    );
  }
}

class ChartData {
  ChartData(this.x, this.y);
  final double x;
  final double y;
}
