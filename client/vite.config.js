import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import tailwindcss from '@tailwindcss/vite'

// https://vite.dev/config/
export default defineConfig({
  plugins: [
    tailwindcss(),
    react()
  ],
  server: {
    proxy: {
      '/status': {
        target: 'http://192.168.39.120', // Replace with your ESP32 IP
        changeOrigin: true,
        secure: false,
      },
      '/scan': {
        target: 'http://192.168.39.120',
        changeOrigin: true,
        secure: false,
      },
      '/log': {
        target: 'http://192.168.39.120',
        changeOrigin: true,
        secure: false,
      },
      '/decrypt': {
        target: 'http://192.168.39.120',
        changeOrigin: true,
        secure: false,
      },
      '/network': {
        target: 'http://192.168.39.120',
        changeOrigin: true,
        secure: false,
      },
    },
  },
})
