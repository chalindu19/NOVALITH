
import { FC } from "react";
import { AreaChart, Area, XAxis, YAxis, CartesianGrid, Tooltip, ResponsiveContainer } from 'recharts';

const data = [
  { year: '2019', rate: 8.2 },
  { year: '2020', rate: 8.4 },
  { year: '2021', rate: 8.7 },
  { year: '2022', rate: 9.6 },
  { year: '2023', rate: 10.5 },
];

const StatisticsSection: FC = () => {
  return (
    <section id="features" className="py-20 bg-white">
      <div className="container mx-auto px-6">
        <div className="grid md:grid-cols-2 gap-12">
          <div className="animate-fade-up">
            <h2 className="text-4xl font-bold text-brand-600 mb-8">The Challenge</h2>
            <div className="space-y-6">
              <div className="flex items-start space-x-4 hover:translate-x-2 transform transition-all duration-300">
                <div className="w-2 h-2 rounded-full bg-brand-500 mt-2" />
                <div>
                  <h3 className="text-xl font-semibold text-brand-600 mb-2">Lack of Continuous Monitoring</h3>
                  <p className="text-gray-600">Current pregnancy care lacks real-time monitoring capabilities.</p>
                </div>
              </div>
              <div className="flex items-start space-x-4 hover:translate-x-2 transform transition-all duration-300">
                <div className="w-2 h-2 rounded-full bg-brand-500 mt-2" />
                <div>
                  <h3 className="text-xl font-semibold text-brand-600 mb

-2">Rising Stillbirth Rates</h3>
                  <p className="text-gray-600">Increasing maternal health risks need early detection solutions.</p>
                </div>
              </div>
              <div className="flex items-start space-x-4 hover:translate-x-2 transform transition-all duration-300">
                <div className="w-2 h-2 rounded-full bg-brand-500 mt-2" />
                <div>
                  <h3 className="text-xl font-semibold text-brand-600 mb-2">Underserved Rural Areas</h3>
                  <p className="text-gray-600">Limited access to quality maternal healthcare in remote regions.</p>
                </div>
              </div>
            </div>
          </div>
          <div className="h-80 animate-fade-up delay-200">
            <h3 className="text-xl font-semibold text-brand-600 mb-4">Stillbirth Statistics in Sri Lanka</h3>
            <ResponsiveContainer width="100%" height="100%">
              <AreaChart data={data}>
                <defs>
                  <linearGradient id="colorRate" x1="0" y1="0" x2="0" y2="1">
                    <stop offset="5%" stopColor="#0077B5" stopOpacity={0.8}/>
                    <stop offset="95%" stopColor="#0077B5" stopOpacity={0.1}/>
                  </linearGradient>
                </defs>
                <CartesianGrid strokeDasharray="3 3" stroke="#eee" />
                <XAxis dataKey="year" stroke="#666" />
                <YAxis stroke="#666" />
                <Tooltip
                  contentStyle={{
                    backgroundColor: 'white',
                    border: '1px solid #ddd',
                    borderRadius: '8px',
                    padding: '10px'
                  }}
                />
                <Area
                  type="monotone"
                  dataKey="rate"
                  stroke="#0077B5"
                  fill="url(#colorRate)"
                  strokeWidth={3}
                  animationDuration={2000}
                  animationEasing="ease-in-out"
                />
              </AreaChart>
            </ResponsiveContainer>
          </div>
        </div>
      </div>
    </section>
  );
};

export default StatisticsSection;
