
import { FC } from "react";

const AISection: FC = () => {
  const startConversation = () => {
    // Get the Convai widget
    const convaiWidget = document.querySelector('elevenlabs-convai');
    if (convaiWidget && convaiWidget.shadowRoot) {
      // Find the start call button inside shadow DOM
      const startButton = convaiWidget.shadowRoot.querySelector('button');
      if (startButton) {
        // Trigger click event
        startButton.click();
      }
    }
  };

  return (
    <section className="py-20 bg-brand-500 text-white">
      <div className="container mx-auto px-6 text-center animate-fade-up">
        <h2 className="text-4xl font-bold mb-8">Talk to Our AI Agent</h2>
        <p className="text-xl mb-8">Get instant answers to your pregnancy health questions</p>
        <button 
          onClick={startConversation}
          className="bg-white text-brand-500 px-8 py-3 rounded-full text-lg font-semibold hover:bg-brand-50 hover:scale-105 transform transition-all duration-300 shadow-lg hover:shadow-xl"
        >
          Start Conversation
        </button>
      </div>
    </section>
  );
};

export default AISection;
