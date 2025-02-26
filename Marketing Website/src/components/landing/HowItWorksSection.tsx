
import { FC } from "react";
import { Heart, BarChart, Cloud, Smartphone } from "lucide-react";

const HowItWorksSection: FC = () => {
  return (
    <section className="py-20 bg-white">
      <div className="container mx-auto px-6">
        <h2 className="text-4xl font-bold text-brand-600 text-center mb-16">How It Works</h2>
        <div className="grid grid-cols-1 md:grid-cols-4 gap-8">
          {[
            { icon: <Heart className="h-8 w-8" />, title: "Sensors", description: "Advanced sensors for detection" },
            { icon: <BarChart className="h-8 w-8" />, title: "Processing", description: "Real-time data analysis" },
            { icon: <Cloud className="h-8 w-8" />, title: "Cloud Storage", description: "Secure data storage" },
            { icon: <Smartphone className="h-8 w-8" />, title: "Mobile App", description: "Easy access interface" },
          ].map((step, index) => (
            <div key={index} className="text-center">
              <div className="bg-brand-50 w-16 h-16 mx-auto rounded-full flex items-center justify-center text-brand-500 mb-4">
                {step.icon}
              </div>
              <h3 className="text-xl font-semibold text-brand-600 mb-2">{step.title}</h3>
              <p className="text-gray-600">{step.description}</p>
            </div>
          ))}
        </div>
      </div>
    </section>
  );
};

export default HowItWorksSection;
