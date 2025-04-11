import React, { useState } from 'react';

const PricingWithContactForm = () => {
  const [showModal, setShowModal] = useState(false);
  const [selectedPlan, setSelectedPlan] = useState('');
  const [formData, setFormData] = useState({
    name: '',
    email: '',
    message: '',
  });
  const [submitted, setSubmitted] = useState(false);

  const handleOpenModal = (plan) => {
    setSelectedPlan(plan);
    setShowModal(true);
    setSubmitted(false);
    setFormData({ name: '', email: '', message: '' });
  };

  const handleCloseModal = () => {
    setShowModal(false);
  };

  const handleChange = (e) => {
    setFormData({ ...formData, [e.target.name]: e.target.value });
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    console.log('Submitted for:', selectedPlan, formData);
    setSubmitted(true);
  };

  return (
    <div className="min-h-screen bg-[#0d0d1a] text-white p-10">
      <h1 className="text-4xl font-bold text-center mb-10 bg-gradient-to-r from-purple-400 to-fuchsia-500 bg-clip-text text-transparent">
        AIR-WALL Pricing Plans
      </h1>

      <div className="grid md:grid-cols-3 gap-6 max-w-6xl mx-auto">
        {/* Basic */}
        <div className="bg-[#1a1a2e] p-6 rounded-2xl shadow-lg border border-purple-800">
          <h2 className="text-xl font-semibold text-yellow-400 mb-2">Basic</h2>
          <p className="text-gray-400 mb-4">Essential cybersecurity tools to get started</p>
          <div className="text-4xl font-bold mb-4">₹700</div>
          <button className="w-full bg-white text-black font-semibold py-2 rounded-xl mb-4">
            Purchase
          </button>
          <ul className="space-y-2 text-sm text-purple-300">
            <li>✔ Network scanning and monitoring</li>
            <li>✔ Wi-Fi analyzer and vulnerability detection</li>
            <li>✔ Basic real-time threat alerts</li>
          </ul>
        </div>

        {/* Premium */}
        <div className="bg-[#1a1a2e] p-6 rounded-2xl shadow-lg border border-purple-800">
          <h2 className="text-xl font-semibold text-purple-400 mb-2">Premium</h2>
          <p className="text-gray-400 mb-4">This plan will be available soon with extended features.</p>
          <button
            className="w-full bg-gradient-to-r from-fuchsia-600 to-purple-600 py-2 rounded-xl font-semibold hover:from-fuchsia-500 hover:to-purple-500 transition"
            onClick={() => handleOpenModal('Premium')}
          >
            Contact Us
          </button>
          <ul className="mt-4 space-y-2 text-sm text-purple-300">
            <li>✔ Advanced real-time network monitoring</li>
            <li>✔ Automated port scanning and vulnerability alerts</li>
            <li>✔ Customizable firewall configurations</li>
            <li>✔ Email and SMS intrusion notifications</li>
          </ul>
        </div>

        {/* Enterprise */}
        <div className="bg-[#1a1a2e] p-6 rounded-2xl shadow-lg border border-purple-800">
          <h2 className="text-xl font-semibold text-red-400 mb-2">Enterprise</h2>
          <p className="text-gray-400 mb-4">Tailored solutions coming soon for large-scale needs.</p>
          <button
            className="w-full bg-gradient-to-r from-fuchsia-600 to-purple-600 py-2 rounded-xl font-semibold hover:from-fuchsia-500 hover:to-purple-500 transition"
            onClick={() => handleOpenModal('Enterprise')}
          >
            Contact Us
          </button>
          <ul className="mt-4 space-y-2 text-sm text-purple-300">
            <li>✔ Full-suite cybersecurity dashboard</li>
            <li>✔ Wi-Fi analyzer with rogue device detection</li>
            <li>✔ Data encryption for local & cloud files</li>
            <li>✔ Dedicated support with SLA</li>
          </ul>
        </div>
      </div>

      {/* Contact Modal */}
      {showModal && (
        <div className="fixed inset-0 bg-black bg-opacity-70 flex items-center justify-center z-50">
          <div className="bg-[#1a1a2e] w-full max-w-lg p-8 rounded-2xl shadow-2xl border border-purple-700 relative">
            <button
              className="absolute top-4 right-4 text-white text-xl font-bold hover:text-red-400"
              onClick={handleCloseModal}
            >
              &times;
            </button>
            <h2 className="text-2xl font-bold mb-6 text-center bg-gradient-to-r from-purple-500 to-fuchsia-500 bg-clip-text text-transparent">
              Contact Us for {selectedPlan} Plan
            </h2>

            {submitted ? (
              <p className="text-green-400 text-center">Thanks! We’ll be in touch soon.</p>
            ) : (
              <form onSubmit={handleSubmit} className="space-y-5">
                <div>
                  <label className="block mb-1 text-sm font-medium">Name</label>
                  <input
                    type="text"
                    name="name"
                    className="w-full p-3 rounded-xl bg-[#121229] border border-purple-500 focus:outline-none focus:ring-2 focus:ring-purple-600"
                    placeholder="Your Name"
                    value={formData.name}
                    onChange={handleChange}
                    required
                  />
                </div>

                <div>
                  <label className="block mb-1 text-sm font-medium">Email</label>
                  <input
                    type="email"
                    name="email"
                    className="w-full p-3 rounded-xl bg-[#121229] border border-purple-500 focus:outline-none focus:ring-2 focus:ring-purple-600"
                    placeholder="Your Email"
                    value={formData.email}
                    onChange={handleChange}
                    required
                  />
                </div>

                <div>
                  <label className="block mb-1 text-sm font-medium">Message</label>
                  <textarea
                    name="message"
                    rows="4"
                    className="w-full p-3 rounded-xl bg-[#121229] border border-purple-500 focus:outline-none focus:ring-2 focus:ring-purple-600"
                    placeholder="Your Message..."
                    value={formData.message}
                    onChange={handleChange}
                    required
                  />
                </div>

                <button
                  type="submit"
                  className="w-full py-3 rounded-xl bg-gradient-to-r from-fuchsia-600 to-purple-600 hover:from-fuchsia-500 hover:to-purple-500 font-semibold transition duration-300"
                >
                  Send Message
                </button>
              </form>
            )}
          </div>
        </div>
      )}
    </div>
  );
};

export default PricingWithContactForm;
