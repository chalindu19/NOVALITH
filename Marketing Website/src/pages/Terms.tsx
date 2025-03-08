import Navigation from "@/components/Navigation";
import FooterSection from "@/components/landing/FooterSection";
import { ScrollText } from "lucide-react";

const Terms = () => {
  return (
    <div className="min-h-screen bg-white">
      <Navigation />

      <section className="pt-32 pb-20">
        <div className="container mx-auto px-6 max-w-4xl">
          <h1 className="text-4xl font-bold text-brand-600 text-center mb-16">Terms of Service</h1>
          
          <div className="space-y-8">
            <div className="prose max-w-none">
              <h2 className="text-2xl font-semibold text-brand-600 mb-4">1. Device Usage</h2>
              <p className="text-gray-600">
                The Smart Pregnancy Belly Wrap is designed for monitoring purposes only and should not replace regular medical check-ups or professional medical advice.
              </p>

              <h2 className="text-2xl font-semibold text-brand-600 mb-4 mt-8">2. User Responsibilities</h2>
              <ul className="list-disc pl-5 space-y-2 text-gray-600">
                <li>Follow all usage instructions carefully</li>
                <li>Keep the device clean and properly maintained</li>
                <li>Report any malfunctions immediately</li>
                <li>Do not modify or attempt to repair the device</li>
              </ul>

              <h2 className="text-2xl font-semibold text-brand-600 mb-4 mt-8">3. Liability Limitations</h2>
              <p className="text-gray-600">
                While we strive for accuracy, we cannot guarantee 100% accuracy of readings. Always consult healthcare providers for medical decisions.
              </p>

              <h2 className="text-2xl font-semibold text-brand-600 mb-4 mt-8">4. Intellectual Property</h2>
              <p className="text-gray-600">
                All software, designs, and content associated with the Smart Pregnancy Belly Wrap are protected by intellectual property laws.
              </p>
            </div>
          </div>
        </div>
      </section>

      <FooterSection />
    </div>
  );
};

export default Terms;
