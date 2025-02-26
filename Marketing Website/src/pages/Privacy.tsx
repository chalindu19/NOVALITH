import Navigation from "@/components/Navigation";
import FooterSection from "@/components/landing/FooterSection";
import { Shield, Lock, Database } from "lucide-react";

const Privacy = () => {
  return (
    <div className="min-h-screen bg-white">
      <Navigation />

      <section className="pt-32 pb-20">
        <div className="container mx-auto px-6 max-w-4xl">
          <h1 className="text-4xl font-bold text-brand-600 text-center mb-16">Privacy Policy</h1>
          
          <div className="space-y-12">
            <div className="space-y-4">
              <div className="flex items-center space-x-4 text-brand-600">
                <Shield className="h-8 w-8" />
                <h2 className="text-2xl font-semibold">Data Protection</h2>
              </div>
              <p className="text-gray-600">
                We prioritize the protection of your sensitive medical data. All information collected through our Smart Pregnancy Belly Wrap is encrypted and stored securely in compliance with HIPAA and GDPR regulations.
              </p>
            </div>

            <div className="space-y-4">
              <div className="flex items-center space-x-4 text-brand-600">
                <Lock className="h-8 w-8" />
                <h2 className="text-2xl font-semibold">Data Collection & Usage</h2>
              </div>
              <p className="text-gray-600">
                We collect and process the following types of data:
              </p>
              <ul className="list-disc pl-5 space-y-2 text-gray-600">
                <li>Maternal vital signs</li>
                <li>Fetal health indicators</li>
                <li>Device usage statistics</li>
                <li>App interaction data</li>
              </ul>
            </div>

            <div className="space-y-4">
              <div className="flex items-center space-x-4 text-brand-600">
                <Database className="h-8 w-8" />
                <h2 className="text-2xl font-semibold">Third-Party Services</h2>
              </div>
              <p className="text-gray-600">
                We partner with industry-leading cloud service providers to ensure secure data storage and processing. All partners are contractually bound to maintain the same level of data protection standards.
              </p>
            </div>
          </div>
        </div>
      </section>

      <FooterSection />
    </div>
  );
};

export default Privacy;
