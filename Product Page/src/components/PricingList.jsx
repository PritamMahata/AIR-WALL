import { check } from "../assets";
import { pricing } from "../constants";
import Button from "./Button";
import Swal from 'sweetalert2';

const PricingList = () => {
  const loadRazorpay = () => {
    return new Promise((resolve) => {
      const script = document.createElement("script");
      script.src = "https://checkout.razorpay.com/v1/checkout.js";
      script.onload = () => resolve(true);
      script.onerror = () => resolve(false);
      document.body.appendChild(script);
    });
  };
  
  const handlePayment = async (item) => {
    const res = await loadRazorpay();
    if (!res) {
      alert("Razorpay SDK failed to load. Are you online?");
      return;
    }
  
    const options = {
      key: import.meta.env.VITE_RAZORPAY_KEY_ID,
      amount: item.price * 100,  
      currency: "INR",
      name: item.title,
      description: item.description,
      image: "/logo.png", // optional logo
      handler: function (response) {
        Swal.fire({
          title: '🎉 Payment Successful!',
          text: `Your payment ID is: ${response.razorpay_payment_id}`,
          icon: 'success',
          confirmButtonText: 'OK',
          background: '#1a1a1a',
          color: '#fff',
          confirmButtonColor: '#00c897',
        });
      },
      prefill: {
        name: "Tuhin Ghosh",
        email: "someone@example.com",
        contact: "9999999999",
      },
      theme: {
        color: "#3399cc",
      },
    };
  
    const paymentObject = new window.Razorpay(options);
    paymentObject.open();
  };
  

  return (
    <div className="flex gap-[1rem] max-lg:flex-wrap">
      {pricing.map((item) => (
        <div
          key={item.id}
          className="w-[19rem] max-lg:w-full h-full px-6 bg-n-8 border border-n-6 rounded-[2rem] lg:w-auto even:py-14 odd:py-8 odd:my-4 [&>h4]:first:text-color-2 [&>h4]:even:text-color-1 [&>h4]:last:text-color-3"
        >
          <h4 className="h4 mb-4">{item.title}</h4>

          <p className="body-2 min-h-[4rem] mb-3 text-n-1/50">
            {item.description}
          </p>

          <div className="flex items-center h-[5.5rem] mb-6">
            {item.price && (
              <>
                <div className="h3">  ₹</div>
                <div className="text-[5.5rem] leading-none font-bold">
                  {item.price}
                </div>
              </>
            )}
          </div>

          <Button
  className="w-full mb-6"
  onClick={() => item.price ? handlePayment(item) : window.location.href = "mailto:contact@jsmastery.pro"}
  white={!!item.price}
>
  {item.price ? "Purchase" : "Contact us"}
</Button>



          <ul>
            {item.features.map((feature, index) => (
              <li
                key={index}
                className="flex items-start py-5 border-t border-n-6"
              >
                <img src={check} width={24} height={24} alt="Check" />
                <p className="body-2 ml-4">{feature}</p>
              </li>
            ))}
          </ul>
        </div>
      ))}
    </div>
  );
};

export default PricingList;
