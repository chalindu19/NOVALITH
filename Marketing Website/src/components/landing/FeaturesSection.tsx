
import { FC } from "react";
import { Heart, Shield, BookOpen, BarChart, MessageCircle, Globe } from "lucide-react";

const FeaturesSection: FC = () => {
  return (
    <section className="py-20 bg-brand-50">
      <div className="container mx-auto px-6">
        <h2 className="text-4xl font-bold text-brand-600 text-center mb-16">Key Features</h2>
        <div className="grid grid-cols-1 md:grid-cols-3 gap-8">
          {[
            {
              icon: <Heart className="h-8 w-8" />,
              title: "Continuous Monitoring",
              description: "24/7 tracking of vital signs and health data",
            },
            {
              icon: <Shield className="h-8 w-8" />,
              title: "Comfort & Portability",
              description: "Lightweight, comfortable design for everyday use",
            },
            {
              icon: <BookOpen className="h-8 w-8" />,
              title: "Educational Resources",
              description: "Access to maternal health guides and tips",
            },
            {
              icon: <BarChart className="h-8 w-8" />,
              title: "AI-Driven Insights",
              description: "Advanced analytics for personalized care",
            },
            {
              icon: <MessageCircle className="h-8 w-8" />,
              title: "AI Agent Support",
              description: "24/7 intelligent healthcare assistance",
            },
            {
              icon: <Globe className="h-8 w-8" />,
              title: "Health Records",
              description: "Comprehensive pregnancy journey tracking",
            },
          ].map((feature, index) => (
            <div key={index} className="bg-white p-8 rounded-lg shadow-lg hover:shadow-xl transition-shadow">
              <div className="text-brand-500 mb-4">{feature.icon}</div>
              <h3 className="text-xl font-semibold text-brand-600 mb-2">{feature.title}</h3>
              <p className="text-gray-600">{feature.description}</p>
            </div>
          ))}
        </div>
      </div>
    </section>
  );
};

export default FeaturesSection;
