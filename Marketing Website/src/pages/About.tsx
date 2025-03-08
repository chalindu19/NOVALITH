import Navigation from "@/components/Navigation";
import FooterSection from "@/components/landing/FooterSection";
import { Target, Heart, Users, Mail, Linkedin } from "lucide-react";
import { useEffect } from "react";

const About = () => {
  const teamMembers = [
    {
      name: "Chalindu Yohan",
      role: "Project Manager",
      image: "/lovable-uploads/135cae48-3df4-4fcd-9414-4d3ff97acbd6.png",
      linkedin: "www.linkedin.com/in/chalinduyohan23",
      email: "chalindu.20230191@iit.ac.lk"
    },
    {
      name: "Minon Perera",
      role: "Business Analysis",
      image: "/lovable-uploads/b17b76b1-89b4-4470-bc51-a0fff5d39312.png",
      linkedin: "https://www.linkedin.com/in/minon-perera-0b9057268/",
      email: "chameth.20230149@iit.ac.lk"
    },
    {
      name: "Crishka Dalpadathu",
      role: "Subject Matter Expert",
      image: "/lovable-uploads/54f0fd3d-2173-4173-bd5f-ab5799ff0557.png",
      linkedin: "https://www.linkedin.com/in/crishka-dalpathadu-1a6062294/",
      email: "crishka.20230242@iit.ac.lk"
    },
    {
      name: "Nadil Dinsara",
      role: "UI/UX Designer",
      image: "/lovable-uploads/87b7c143-990a-46e8-9973-a60264a67db9.png",
      linkedin: "https://www.linkedin.com/in/nadil-dinsara-870ab8294/",
      email: "nadil.20230193@iit.ac.lk"
    },
    {
      name: "Banura Yomal",
      role: "Resource Manager",
      image: "/lovable-uploads/9576d2b6-0f2d-4570-bf68-b18785c8e756.png",
      linkedin: "https://www.linkedin.com/in/banura-yomal-de-silva-798783294/",
      email: "banura.20230262@iit.ac.lk"
    },
    {
      name: "Sandun Anjana",
      role: "Risk Manager",
      image: "/lovable-uploads/c601a257-afe9-406d-8291-6ddd19754674.png",
      linkedin: "https://www.linkedin.com/in/sandun-anjana-560041294/",
      email: "sandun.20230122@iit.ac.lk"
    }
  ];

  const values = [
    "Innovation in Healthcare Technology",
    "Excellence in Service Delivery",
    "Integrity in Data Protection",
    "Collaborative Healthcare Solutions",
    "Patient Empowerment",
    "Social Responsibility"
  ];

  useEffect(() => {
    const observerOptions = {
      threshold: 0.1,
    };

    const observer = new IntersectionObserver((entries) => {
      entries.forEach((entry) => {
        if (entry.isIntersecting) {
          entry.target.classList.add("animate-fade-up");
          observer.unobserve(entry.target);
        }
      });
    }, observerOptions);

    document.querySelectorAll(".animate-on-scroll").forEach((el) => {
      observer.observe(el);
    });

    return () => observer.disconnect();
  }, []);

  return (
    <div className="min-h-screen bg-white">
      <Navigation />

      {/* Hero Section */}
      <section className="relative h-[60vh] flex items-center justify-center">
        <div className="absolute inset-0">
          <img
            src="/lovable-uploads/1f845df2-39d5-4c8f-a38c-33726949deb4.png"
            alt="Team"
            className="w-full h-full object-cover"
          />
          <div className="absolute inset-0 bg-brand-600/70" />
        </div>
        <div className="relative z-10 text-center text-white px-6">
          <h1 className="text-5xl md:text-6xl font-bold mb-6 animate-fade-up">Meet Our Team</h1>
          <p className="text-xl md:text-2xl max-w-3xl mx-auto animate-fade-up delay-100">
            Together, we're revolutionizing maternal healthcare through innovation and dedication
          </p>
        </div>
      </section>

      <section id="mission" className="py-20">
        <div className="container mx-auto px-6">
          {/* Mission Section */}
          <div className="max-w-4xl mx-auto mb-20 animate-on-scroll">
            <div className="flex items-center justify-center mb-8 text-brand-600">
              <Target className="h-12 w-12" />
            </div>
            <h2 className="text-4xl font-bold text-center text-brand-600 mb-8">Our Mission</h2>
            <p className="text-xl text-gray-600 text-center leading-relaxed">
              We are dedicated to revolutionizing maternal healthcare through innovative technology solutions. 
              Our mission is to empower expectant mothers and healthcare providers with real-time monitoring 
              and data-driven insights, ensuring safer pregnancies and better healthcare outcomes.
            </p>
          </div>

          {/* Values Section */}
          <div id="values" className="max-w-4xl mx-auto mb-20 animate-on-scroll">
            <div className="flex items-center justify-center mb-8 text-brand-600">
              <Heart className="h-12 w-12" />
            </div>
            <h2 className="text-4xl font-bold text-center text-brand-600 mb-8">Our Values</h2>
            <div className="grid md:grid-cols-2 gap-6">
              {values.map((value, index) => (
                <div 
                  key={index}
                  className="p-6 bg-white rounded-lg shadow-lg hover:shadow-xl transition-shadow duration-300 border border-brand-100"
                >
                  <p className="text-lg text-gray-700 font-medium">{value}</p>
                </div>
              ))}
            </div>
          </div>

          {/* Team Section */}
          <div id="team" className="animate-on-scroll">
            <div className="flex items-center justify-center mb-8 text-brand-600">
              <Users className="h-12 w-12" />
            </div>
            <h2 className="text-4xl font-bold text-center text-brand-600 mb-16">Our Team</h2>
            <div className="grid md:grid-cols-2 lg:grid-cols-3 gap-8">
              {teamMembers.map((member, index) => (
                <div
                  key={index}
                  className="bg-white rounded-xl shadow-lg hover:shadow-xl transition-shadow duration-300 overflow-hidden"
                >
                  <div className="h-80 overflow-hidden">
                    <img
                      src={member.image}
                      alt={member.name}
                      className="w-full h-full object-cover object-center"
                    />
                  </div>
                  <div className="p-6">
                    <h3 className="text-xl font-semibold text-brand-600 mb-2">{member.name}</h3>
                    <p className="text-gray-600 mb-4">{member.role}</p>
                    <div className="flex space-x-4">
                      <a
                        href={member.linkedin}
                        target="_blank"
                        rel="noopener noreferrer"
                        className="flex items-center text-brand-500 hover:text-brand-600 transition-colors"
                      >
                        <Linkedin className="h-5 w-5" />
                      </a>
                      <a
                        href={`mailto:${member.email}`}
                        className="flex items-center text-brand-500 hover:text-brand-600 transition-colors"
                      >
                        <Mail className="h-5 w-5" />
                      </a>
                    </div>
                  </div>
                </div>
              ))}
            </div>
          </div>
        </div>
      </section>

      <FooterSection />
    </div>
  );
};

export default About;
