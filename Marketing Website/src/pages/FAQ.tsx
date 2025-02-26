import Navigation from "@/components/Navigation";
import FooterSection from "@/components/landing/FooterSection";
import { Plus, Minus } from "lucide-react";
import { useState } from "react";

const FAQ = () => {
  const [openIndex, setOpenIndex] = useState<number | null>(null);

  const faqs = [
    {
      question: "How long can I wear the Smart Pregnancy Belly Wrap?",
      answer: "The wrap is designed for comfortable, extended wear up to 12 hours per day. We recommend taking breaks every 4 hours and avoiding wear during sleep."
    },
    {
      question: "How do the real-time alerts work?",
      answer: "The device continuously monitors vital signs and uses AI to detect any concerning patterns. If detected, immediate notifications are sent to your phone and your healthcare provider."
    },
    {
      question: "Is my health data secure?",
      answer: "Yes, we use medical-grade encryption and comply with HIPAA/GDPR standards. Your data is stored securely and only accessible to you and your authorized healthcare providers."
    },
    {
      question: "Which devices is the app compatible with?",
      answer: "Our app works with iOS 13+ and Android 8+ devices. The wrap connects via Bluetooth 5.0 for reliable, low-energy data transmission."
    },
    {
      question: "How does cloud integration work?",
      answer: "Data is automatically synced to our secure cloud platform, allowing real-time access for you and your healthcare team through the mobile app or web dashboard."
    },
    {
      question: "What's the battery life of the device?",
      answer: "The device typically lasts 24-36 hours on a single charge. Wireless charging takes approximately 2 hours for a full charge."
    },
    {
      question: "Are there any subscription fees?",
      answer: "The basic monitoring service is included with device purchase. Premium features like AI insights and extended data storage are available through our subscription plans."
    },
    {
      question: "What's covered under warranty?",
      answer: "Our devices come with a 1-year limited warranty covering manufacturing defects and hardware malfunctions under normal use."
    },
    {
      question: "How do I clean the device?",
      answer: "The fabric portion can be hand-washed with mild soap. The sensor module can be wiped clean with medical-grade sanitizing wipes."
    },
    {
      question: "How do I contact support?",
      answer: "Our support team is available 24/7 through the app, email at support@novalith.care, or phone at (+94)70 363 6366."
    }
  ];

  return (
    <div className="min-h-screen bg-white">
      <Navigation />
      <section className="pt-32 pb-20">
        <div className="container mx-auto px-6 max-w-4xl">
          <h1 className="text-4xl font-bold text-brand-600 text-center mb-16">Frequently Asked Questions</h1>
          
          <div className="space-y-4">
            {faqs.map((faq, index) => (
              <div key={index} className="border border-gray-200 rounded-lg">
                <button
                  className="w-full px-6 py-4 flex items-center justify-between text-left"
                  onClick={() => setOpenIndex(openIndex === index ? null : index)}
                >
                  <span className="font-semibold text-brand-600">{faq.question}</span>
                  {openIndex === index ? (
                    <Minus className="h-5 w-5 text-brand-500" />
                  ) : (
                    <Plus className="h-5 w-5 text-brand-500" />
                  )}
                </button>
                {openIndex === index && (
                  <div className="px-6 pb-4 text-gray-600">
                    {faq.answer}
                  </div>
                )}
              </div>
            ))}
          </div>
        </div>
      </section>
      <FooterSection />
    </div>
  );
};

export default FAQ;
