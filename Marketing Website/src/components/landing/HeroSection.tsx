
import { FC } from "react";
import HeroCarousel from "./HeroCarousel";
import { useNavigate } from "react-router-dom";

const HeroSection: FC = () => {
  const navigate = useNavigate();

  const goToHome = () => {
    navigate('/');
    window.scrollTo({ top: 0, behavior: 'smooth' });
  };

  return (
    <section className="relative h-screen flex items-center justify-center bg-brand-500" aria-label="Hero Section">
      <HeroCarousel />

      <div className="container mx-auto px-6 text-center relative z-10">
        <h1 className="text-4xl sm:text-5xl md:text-6xl font-bold text-white mb-6 animate-fade-up">
          Transforming Maternal Healthcare
        </h1>
        <p className="text-lg sm:text-xl text-white/90 mb-8 animate-fade-up delay-100 max-w-2xl mx-auto">
          Advanced monitoring for safer pregnancies and healthier futures
        </p>
        <button
          onClick={() => document.getElementById("features")?.scrollIntoView({ behavior: "smooth" })}
          className="bg-white text-brand-500 px-6 sm:px-8 py-3 rounded-full text-lg font-semibold 
                   hover:bg-brand-50 hover:scale-105 transform transition-all duration-300 
                   shadow-lg hover:shadow-xl animate-fade-up delay-200"
          aria-label="Learn more about our features"
        >
          Learn More
        </button>
      </div>

      <div className="absolute bottom-8 left-0 right-0 flex justify-center gap-2 z-10">
        {Array.from({ length: 5 }).map((_, index) => (
          <div
            key={index}
            className={`h-2 transition-all duration-300 rounded-full ${
              index === 0 ? "w-8 bg-white" : "bg-white/50 w-2"
            }`}
            role="button"
            aria-label={`Go to slide ${index + 1}`}
            tabIndex={0}
          />
        ))}
      </div>
    </section>
  );
};

export default HeroSection;
