import React from 'react'
import ReactDOM from 'react-dom/client'
import App from './App'
import './index.css'
import { ClerkProvider } from '@clerk/clerk-react'
import { BrowserRouter } from 'react-router-dom'

const PUBLISHABLE_KEY = import.meta.env.VITE_CLERK_PUBLISHABLE_KEY;

if (!PUBLISHABLE_KEY) {
  throw new Error("Missing Publishable Key")
}

ReactDOM.createRoot(document.getElementById('root')).render(
  <React.StrictMode>
    <ClerkProvider
      appearance={{
        baseTheme: {
          colorScheme: 'dark',
          variables: {
            colorPrimary: '#9b59b6',
            colorText: '#e5d4ef',
            colorTextSecondary: '#c8a2d9',
            colorTextOnPrimary: '#ffffff',
            colorBackground: '#1b1125',
            colorBackgroundSecondary: '#2c1a3a',
            colorInputBackground: '#2e1c3c',
            colorInputText: '#fff',
            colorInputBorder: '#8e44ad',
          },
        },
        elements: {
          userButtonPopoverActionButton: {
            color: '#ffffff',
          },
          userButtonPopoverActionButtonText: {
            color: '#ffffff',
          },
          userButtonPopoverActionButtonIcon: {
            color: '#ffffff',
          },
        },
      }}
    publishableKey={PUBLISHABLE_KEY} afterSignOutUrl="/">
      <BrowserRouter>
        <App />
      </BrowserRouter>
    </ClerkProvider>
  </React.StrictMode>,
)