
import { FC, FormEvent, useState } from "react";
import { Phone, Mail, MapPin } from "lucide-react";

const ContactSection: FC = () => {
  const [formData, setFormData] = useState({
    name: "",
    email: "",
    message: ""
  });
  const [errors, setErrors] = useState({
    name: "",
    email: "",
    message: ""
  });

  const validateForm = () => {
    let isValid = true;
    const newErrors = {
      name: "",
      email: "",
      message: ""
    };

    if (!formData.name.trim()) {
      newErrors.name = "Name is required";
      isValid = false;
    }

    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    if (!formData.email.trim() || !emailRegex.test(formData.email)) {
      newErrors.email = "Valid email is required";
      isValid = false;
    }

    if (!formData.message.trim()) {
      newErrors.message = "Message is required";
      isValid = false;
    }

    setErrors(newErrors);
    return isValid;
  };

  const handleSubmit = (e: FormEvent) => {
    e.preventDefault();
    
    if (validateForm()) {
      const mailtoLink = `mailto:amorhealthcarelk@gmail.com?subject=Contact Form Submission from ${encodeURIComponent(formData.name)}&body=${encodeURIComponent(`Name: ${formData.name}\nEmail: ${formData.email}\n\nMessage:\n${formData.message}`)}`;
      window.location.href = mailtoLink;
      
      // Reset form after submission
      setFormData({
        name: "",
        email: "",
        message: ""
      });
    }
  };

  return (
    <section id="contact" className="py-20 bg-white">
      <div className="container mx-auto px-6">
        <h2 className="text-4xl font-bold text-brand-600 text-center mb-16 animate-fade-up">Get in Touch</h2>
        <div className="max-w-4xl mx-auto">
          <div className="grid md:grid-cols-2 gap-12">
            <div className="space-y-8 animate-fade-up delay-100">
              <a 
                href="tel:+94703636366" 
                className="flex items-center space-x-4 hover:text-brand-500 transition-colors group"
              >
                <Phone className="h-6 w-6 text-brand-500 group-hover:scale-110 transition-transform" />
                <p className="text-gray-700">(+94)70 363 6366</p>
              </a>
              <a 
                href="mailto:amorhealthcarelk@gmail.com" 
                className="flex items-center space-x-4 hover:text-brand-500 transition-colors group"
              >
                <Mail className="h-6 w-6 text-brand-500 group-hover:scale-110 transition-transform" />
                <p className="text-gray-700">amorhealthcarelk@gmail.com</p>
              </a>
              <a 
                href="https://maps.google.com/?q=435+Galle+Rd,+Colombo+00300" 
                target="_blank" 
                rel="noopener noreferrer" 
                className="flex items-start space-x-4 hover:text-brand-500 transition-colors group"
              >
                <MapPin className="h-6 w-6 text-brand-500 mt-1 group-hover:scale-110 transition-transform" />
                <p className="text-gray-700">435 Galle Rd, Colombo 00300</p>
              </a>
            </div>
            <form onSubmit={handleSubmit} className="space-y-6 animate-fade-up delay-200">
              <div>
                <input
                  type="text"
                  placeholder="Your Name"
                  value={formData.name}
                  onChange={(e) => setFormData({ ...formData, name: e.target.value })}
                  className={`w-full px-4 py-3 rounded-lg border ${
                    errors.name ? 'border-red-500' : 'border-gray-300'
                  } focus:outline-none focus:border-brand-500 focus:ring-2 focus:ring-brand-500/20 transition-all duration-300`}
                />
                {errors.name && <p className="text-red-500 text-sm mt-1">{errors.name}</p>}
              </div>
              <div>
                <input
                  type="email"
                  placeholder="Your Email"
                  value={formData.email}
                  onChange={(e) => setFormData({ ...formData, email: e.target.value })}
                  className={`w-full px-4 py-3 rounded-lg border ${
                    errors.email ? 'border-red-500' : 'border-gray-300'
                  } focus:outline-none focus:border-brand-500 focus:ring-2 focus:ring-brand-500/20 transition-all duration-300`}
                />
                {errors.email && <p className="text-red-500 text-sm mt-1">{errors.email}</p>}
              </div>
              <div>
                <textarea
                  placeholder="Your Message"
                  rows={4}
                  value={formData.message}
                  onChange={(e) => setFormData({ ...formData, message: e.target.value })}
                  className={`w-full px-4 py-3 rounded-lg border ${
                    errors.message ? 'border-red-500' : 'border-gray-300'
                  } focus:outline-none focus:border-brand-500 focus:ring-2 focus:ring-brand-500/20 transition-all duration-300`}
                />
                {errors.message && <p className="text-red-500 text-sm mt-1">{errors.message}</p>}
              </div>
              <button 
                type="submit"
                className="w-full bg-brand-500 text-white px-6 py-3 rounded-lg font-semibold hover:bg-brand-600 hover:scale-105 transform transition-all duration-300 shadow-lg hover:shadow-xl"
              >
                Send Message
              </button>
            </form>
          </div>
        </div>
      </div>
    </section>
  );
};

export default ContactSection;
