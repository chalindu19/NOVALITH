
import { FC } from "react";
import Navigation from "@/components/Navigation";
import FooterSection from "@/components/landing/FooterSection";
import { Shield, Cpu, Database, Smartphone, Heart, Activity, Bell, Cloud } from "lucide-react";

const Design: FC = () => {
  return (
    <div className="min-h-screen bg-white">
      <Navigation />

      {/* Hero Section */}
      <section className="relative h-[60vh] flex items-center justify-center">
        <div className="absolute inset-0">
          <img
            src="/lovable-uploads/a26f29ae-30ac-4a80-a49b-901a1b554d30.png"
            alt="Design Process"
            className="w-full h-full object-cover"
          />
          <div className="absolute inset-0 bg-brand-600/70" />
        </div>
        <div className="relative z-10 text-center text-white px-6">
          <h1 className="text-5xl md:text-6xl font-bold mb-6 animate-fade-up">
            Smart Pregnancy Belly Wrap Design
          </h1>
          <p className="text-xl md:text-2xl max-w-3xl mx-auto animate-fade-up delay-100">
            Advanced wearable technology designed for comprehensive maternal and fetal health monitoring
          </p>
        </div>
      </section>

      {/* Hardware & Software Section */}
      <section className="py-20 bg-white">
        <div className="container mx-auto px-6">
          <div className="grid md:grid-cols-2 gap-12 items-start">
            {/* Hardware Overview */}
            <div className="space-y-8 animate-fade-up delay-200">
              <div>
                <div className="flex items-center space-x-3 mb-6">
                  <Shield className="h-8 w-8 text-brand-500" />
                  <h2 className="text-3xl font-bold text-brand-600">Hardware Overview</h2>
                </div>
                <div className="bg-brand-50 rounded-2xl p-8 space-y-6">
                  <div className="flex items-start space-x-4">
                    <Cpu className="h-6 w-6 text-brand-500 mt-1" />
                    <div>
                      <h3 className="text-xl font-semibold text-brand-600 mb-2">Advanced Sensors</h3>
                      <p className="text-gray-600">Non-invasive biosensors integrated into medical-grade fabric for accurate vital monitoring</p>
                    </div>
                  </div>
                  <div className="flex items-start space-x-4">
                    <Heart className="h-6 w-6 text-brand-500 mt-1" />
                    <div>
                      <h3 className="text-xl font-semibold text-brand-600 mb-2">Real-time Monitoring</h3>
                      <p className="text-gray-600">Continuous tracking of maternal and fetal vital signs with instant data processing</p>
                    </div>
                  </div>
                  <div className="flex items-start space-x-4">
                    <Activity className="h-6 w-6 text-brand-500 mt-1" />
                    <div>
                      <h3 className="text-xl font-semibold text-brand-600 mb-2">Comfort-First Design</h3>
                      <p className="text-gray-600">Ergonomic design with breathable materials for extended comfortable wear</p>
                    </div>
                  </div>
                </div>
              </div>
            </div>

            {/* Software Integration */}
            <div className="space-y-8 animate-fade-up delay-300">
              <div>
                <div className="flex items-center space-x-3 mb-6">
                  <Database className="h-8 w-8 text-brand-500" />
                  <h2 className="text-3xl font-bold text-brand-600">Software Integration</h2>
                </div>
                <div className="bg-brand-50 rounded-2xl p-8 space-y-6">
                  <div className="flex items-start space-x-4">
                    <Cloud className="h-6 w-6 text-brand-500 mt-1" />
                    <div>
                      <h3 className="text-xl font-semibold text-brand-600 mb-2">Secure Cloud Platform</h3>
                      <p className="text-gray-600">End-to-end encrypted data storage and processing with HIPAA compliance</p>
                    </div>
                  </div>
                  <div className="flex items-start space-x-4">
                    <Bell className="h-6 w-6 text-brand-500 mt-1" />
                    <div>
                      <h3 className="text-xl font-semibold text-brand-600 mb-2">Smart Notifications</h3>
                      <p className="text-gray-600">AI-powered alert system for immediate response to concerning patterns</p>
                    </div>
                  </div>
                  <div className="flex items-start space-x-4">
                    <Smartphone className="h-6 w-6 text-brand-500 mt-1" />
                    <div>
                      <h3 className="text-xl font-semibold text-brand-600 mb-2">Mobile Integration</h3>
                      <p className="text-gray-600">User-friendly mobile app for real-time monitoring and historical data analysis</p>
                    </div>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>
      </section>

      {/* Software Prototype Section */}
      <section className="py-20 bg-brand-50">
        <div className="container mx-auto px-6">
          <h2 className="text-3xl font-bold text-brand-600 text-center mb-12">Mobile Application Interface</h2>
          <div className="max-w-md mx-auto bg-white rounded-3xl shadow-xl overflow-hidden animate-fade-up delay-200">
            <img
              src="/lovable-uploads/6633215e-69f6-4b2a-83ea-d6a71fc0d02b.png"
              alt="Smart Pregnancy Belly Wrap Mobile Interface"
              className="w-full h-auto"
            />
            <div className="p-6 space-y-4">
              <h3 className="text-xl font-semibold text-brand-600">Key Features Showcase</h3>
              <ul className="space-y-2 text-gray-600">
                <li className="flex items-center space-x-2">
                  <Heart className="h-4 w-4 text-brand-500" />
                  <span>Real-time vital signs monitoring</span>
                </li>
                <li className="flex items-center space-x-2">
                  <Bell className="h-4 w-4 text-brand-500" />
                  <span>Instant health alerts and notifications</span>
                </li>
                <li className="flex items-center space-x-2">
                  <Shield className="h-4 w-4 text-brand-500" />
                  <span>Secure data encryption and storage</span>
                </li>
                <li className="flex items-center space-x-2">
                  <Smartphone className="h-4 w-4 text-brand-500" />
                  <span>User-friendly mobile interface</span>
                </li>
              </ul>
            </div>
          </div>
        </div>
      </section>

      <FooterSection />
    </div>
  );
};

export default Design;
