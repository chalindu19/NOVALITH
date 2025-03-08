
import { FC } from "react";
import { Heart, Shield, Wifi, Cloud } from "lucide-react";
import SolutionCarousel from "./SolutionCarousel";

const SolutionSection: FC = () => {
  return (
    <section className="py-20 bg-brand-50">
      <div className="container mx-auto px-6">
        <h2 className="text-4xl font-bold text-brand-600 text-center mb-16">
          Introducing Smart Pregnancy Belly Wrap
        </h2>
        <div className="grid md:grid-cols-2 gap-12 items-center">
          <div className="animate-fade-up">
            <SolutionCarousel />
          </div>
          <div className="space-y-8">
            {[
              {
                icon: <Heart className="h-6 w-6 text-brand-500" />,
                title: "Real-time Monitoring",
                description: "Continuous tracking of vital signs and fetal health",
              },
              {
                icon: <Shield className="h-6 w-6 text-brand-500" />,
                title: "Immediate Alerts",
                description: "Instant notifications for any concerning signs",
              },
              {
                icon: <Wifi className="h-6 w-6 text-brand-500" />,
                title: "Remote Access",
                description: "Monitor and access data from anywhere, anytime",
              },
              {
                icon: <Cloud className="h-6 w-6 text-brand-500" />,
                title: "Cloud Integration",
                description: "Secure storage and analysis in real-time",
              },
            ].map((feature, index) => (
              <div 
                key={index} 
                className="flex items-start space-x-4 animate-fade-up"
                style={{ animationDelay: `${index * 100}ms` }}
              >
                <div className="shrink-0">{feature.icon}</div>
                <div>
                  <h3 className="text-xl font-semibold text-brand-600 mb-2">
                    {feature.title}
                  </h3>
                  <p className="text-gray-600">{feature.description}</p>
                </div>
              </div>
            ))}
          </div>
        </div>
      </div>
    </section>
  );
};

export default SolutionSection;
