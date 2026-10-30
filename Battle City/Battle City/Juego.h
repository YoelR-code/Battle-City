
#pragma once
#include "Controladora.h"

namespace Battle {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class Juego : public System::Windows::Forms::Form
    {
    public:
        // Obtener la instancia unica del Singleton.
        CControladora* controladora =
            CControladora::ObtenerInstancia();

        Bitmap^ bmpTanques =
            gcnew Bitmap("imagenes\\tanques.png");

        Bitmap^ bmpNivel1 =
            gcnew Bitmap("imagenes\\fondo-nivel-1.png");

        Bitmap^ bmpNivel2 =
            gcnew Bitmap("imagenes\\fondo-nivel-2.png");

        Bitmap^ bmpNivel3 =
            gcnew Bitmap("imagenes\\fondo-nivel-3.png");

        Bitmap^ bmpNivel4 =
            gcnew Bitmap("imagenes\\fondo-nivel-4.png");

        Bitmap^ bmpNivel5 =
            gcnew Bitmap("imagenes\\fondo-nivel-5.png");

        Juego(void)
        {
            direccionTecla = ninguno;
            nivelActual = 1;
            InitializeComponent();
        }

    protected:
        ~Juego()
        {
            if (timer1 != nullptr)
                timer1->Stop();

            // No eliminar la controladora:
            // pertenece al Singleton.
            controladora = nullptr;

            if (bmpTanques != nullptr)
                delete bmpTanques;

            if (bmpNivel1 != nullptr)
                delete bmpNivel1;

            if (bmpNivel2 != nullptr)
                delete bmpNivel2;

            if (bmpNivel3 != nullptr)
                delete bmpNivel3;

            if (bmpNivel4 != nullptr)
                delete bmpNivel4;

            if (bmpNivel5 != nullptr)
                delete bmpNivel5;

            if (components != nullptr)
                delete components;
        }

    private:
        System::Windows::Forms::Timer^ timer1;
        System::ComponentModel::IContainer^ components;

        EDireccion direccionTecla;
        int nivelActual;

#pragma region Windows Form Designer generated code

        void InitializeComponent(void)
        {
            this->components =
                gcnew System::ComponentModel::Container();

            this->timer1 =
                gcnew System::Windows::Forms::Timer(
                    this->components
                );

            this->SuspendLayout();

            this->timer1->Enabled = false;
            this->timer1->Interval = 60;

            this->timer1->Tick +=
                gcnew System::EventHandler(
                    this,
                    &Juego::timer1_Tick
                );

            this->AutoScaleDimensions =
                System::Drawing::SizeF(6, 13);

            this->AutoScaleMode =
                System::Windows::Forms::AutoScaleMode::Font;

            this->ClientSize =
                System::Drawing::Size(832, 832);

            this->Name = L"Juego";
            this->Text = L"Battle City";

            this->WindowState =
                System::Windows::Forms::FormWindowState::Maximized;

            this->KeyPreview = true;
            this->DoubleBuffered = true;
            this->ResizeRedraw = true;

            this->Load +=
                gcnew System::EventHandler(
                    this,
                    &Juego::Juego_Load
                );

            this->KeyDown +=
                gcnew System::Windows::Forms::KeyEventHandler(
                    this,
                    &Juego::Juego_KeyDown
                );

            this->KeyUp +=
                gcnew System::Windows::Forms::KeyEventHandler(
                    this,
                    &Juego::Juego_KeyUp
                );

            this->ResumeLayout(false);
        }

#pragma endregion

    private:

        Bitmap^ ObtenerFondoActual()
        {
            switch (nivelActual) {
            case 2:
                return bmpNivel2;

            case 3:
                return bmpNivel3;

            case 4:
                return bmpNivel4;

            case 5:
                return bmpNivel5;

            default:
                return bmpNivel1;
            }
        }

        void SeleccionarNivel(int nivel)
        {
            if (controladora == nullptr)
                return;

            Bitmap^ fondo = nullptr;

            switch (nivel) {
            case 1:
                fondo = bmpNivel1;
                break;

            case 2:
                fondo = bmpNivel2;
                break;

            case 3:
                fondo = bmpNivel3;
                break;

            case 4:
                fondo = bmpNivel4;
                break;

            case 5:
                fondo = bmpNivel5;
                break;

            default:
                return;
            }

            nivelActual = nivel;

            controladora->CambiarNivel(
                nivelActual,
                fondo
            );

            direccionTecla = ninguno;
            this->Invalidate();
        }

        System::Void Juego_Load(
            System::Object^ sender,
            System::EventArgs^ e
        ) {
            controladora->Inicializar();

            nivelActual = 1;
            direccionTecla = ninguno;

            timer1->Start();
            this->Focus();
        }

        System::Void Juego_KeyDown(
            System::Object^ sender,
            System::Windows::Forms::KeyEventArgs^ e
        ) {
            switch (e->KeyCode) {
            case Keys::Up:
                direccionTecla = arriba;
                break;

            case Keys::Down:
                direccionTecla = abajo;
                break;

            case Keys::Left:
                direccionTecla = izquierda;
                break;

            case Keys::Right:
                direccionTecla = derecha;
                break;

            case Keys::D1:
            case Keys::NumPad1:
                SeleccionarNivel(1);
                break;

            case Keys::D2:
            case Keys::NumPad2:
                SeleccionarNivel(2);
                break;

            case Keys::D3:
            case Keys::NumPad3:
                SeleccionarNivel(3);
                break;

            case Keys::D4:
            case Keys::NumPad4:
                SeleccionarNivel(4);
                break;

            case Keys::D5:
            case Keys::NumPad5:
                SeleccionarNivel(5);
                break;

            default:
                return;
            }

            e->Handled = true;
            e->SuppressKeyPress = true;
        }

        System::Void Juego_KeyUp(
            System::Object^ sender,
            System::Windows::Forms::KeyEventArgs^ e
        ) {
            if ((e->KeyCode == Keys::Up &&
                direccionTecla == arriba) ||

                (e->KeyCode == Keys::Down &&
                    direccionTecla == abajo) ||

                (e->KeyCode == Keys::Left &&
                    direccionTecla == izquierda) ||

                (e->KeyCode == Keys::Right &&
                    direccionTecla == derecha)) {

                direccionTecla = ninguno;
            }
        }

        System::Void timer1_Tick(
            System::Object^ sender,
            System::EventArgs^ e
        ) {
            if (controladora == nullptr)
                return;

            Bitmap^ fondo = ObtenerFondoActual();

            if (fondo == nullptr)
                return;

            if (direccionTecla != ninguno) {
                controladora->MoverJugador(
                    direccionTecla,
                    fondo
                );
            }

            controladora->MoverEnemigos(fondo);

            Graphics^ g = this->CreateGraphics();

            BufferedGraphicsContext^ espacio =
                BufferedGraphicsManager::Current;

            BufferedGraphics^ buffer =
                espacio->Allocate(
                    g,
                    this->ClientRectangle
                );

            Graphics^ dibujo = buffer->Graphics;

            dibujo->Clear(Color::Black);

            float escalaX =
                (float)this->ClientSize.Width /
                (float)fondo->Width;

            float escalaY =
                (float)this->ClientSize.Height /
                (float)fondo->Height;

            float escala = escalaX;

            if (escalaY < escala)
                escala = escalaY;

            if (escala <= 0.0f)
                escala = 1.0f;

            float anchoMapa = fondo->Width * escala;
            float altoMapa = fondo->Height * escala;

            float desplazamientoX =
                (this->ClientSize.Width - anchoMapa) / 2.0f;

            float desplazamientoY =
                (this->ClientSize.Height - altoMapa) / 2.0f;

            dibujo->ScaleTransform(escala, escala);

            dibujo->TranslateTransform(
                desplazamientoX / escala,
                desplazamientoY / escala
            );

            controladora->DibujarFondo(
                dibujo,
                fondo
            );

            controladora->DibujarTanques(
                dibujo,
                bmpTanques
            );

            buffer->Render(g);

            delete buffer;
            delete g;
        }
    };
}
