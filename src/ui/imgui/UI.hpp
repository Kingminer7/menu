#pragma once

namespace summit::ui::imgui {
    class UI {
        protected:
            UI(){};
            static UI* instance;
        public:
            static UI* get();
            
            void draw();
            void init();
    };

    // @brief Shortcut to get the UI instance
    UI *get() {
        return UI::get();
    }

    // Font currentFont;
    // FontStyle currentFontStyle;

    enum class Font {
        Alegreya,
        Assistant,
        Carme,
        Lato,
        Montserrat,
        Nunito,
        OpenSans,
        OpenSansCondensed,
        OpenSansSemiCondensed,
        Poppins,
        Roboto,
        Ubuntu
    };
    enum class FontStyle {
        Black,
        BlackItalic,
        Bold,
        BoldItalic,
        ExtraBold,
        ExtraBoldItalic,
        ExtraLight,
        ExtraLightItalic,
        Italic,
        Light,
        LightItalic,
        Medium,
        MediumItalic,
        Regular,
        SemiBold,
        SemiBoldItalic,
        Thin,
        ThinItalic
    };
    std::map<Font, std::vector<FontStyle>> availableStyles = {
        {Font::Alegreya, {FontStyle::Black, FontStyle::BlackItalic, FontStyle::Bold, FontStyle::BoldItalic, FontStyle::ExtraBold, FontStyle::ExtraBoldItalic, FontStyle::Italic, FontStyle::Medium, FontStyle::MediumItalic, FontStyle::Regular, FontStyle::SemiBold, FontStyle::SemiBoldItalic}},
        {Font::Assistant, {FontStyle::Bold, FontStyle::ExtraBold, FontStyle::ExtraLight, FontStyle::Light, FontStyle::Medium, FontStyle::Regular, FontStyle::SemiBold}},
        {Font::Carme, {FontStyle::Regular}},
        {Font::Lato, {FontStyle::Black, FontStyle::BlackItalic, FontStyle::Bold, FontStyle::BoldItalic, FontStyle::Italic, FontStyle::Light, FontStyle::LightItalic, FontStyle::Regular, FontStyle::Thin, FontStyle::ThinItalic}},
        {Font::Montserrat, {FontStyle::Black, FontStyle::BlackItalic, FontStyle::Bold, FontStyle::BoldItalic, FontStyle::ExtraBold, FontStyle::ExtraBoldItalic, FontStyle::ExtraLight, FontStyle::ExtraLightItalic, FontStyle::Italic, FontStyle::Medium, FontStyle::MediumItalic, FontStyle::Regular, FontStyle::SemiBold, FontStyle::SemiBoldItalic, FontStyle::Thin, FontStyle::ThinItalic}},
        {Font::Nunito, {FontStyle::Black, FontStyle::BlackItalic, FontStyle::Bold, FontStyle::BoldItalic, FontStyle::ExtraBold, FontStyle::ExtraBoldItalic, FontStyle::ExtraLight, FontStyle::ExtraLightItalic, FontStyle::Italic, FontStyle::Light, FontStyle::LightItalic, FontStyle::Medium, FontStyle::MediumItalic, FontStyle::Regular, FontStyle::SemiBold, FontStyle::SemiBoldItalic}},
        {Font::OpenSans, {FontStyle:: Bold, FontStyle::BoldItalic, FontStyle::ExtraBold, FontStyle::ExtraBoldItalic, FontStyle::Italic, FontStyle::Light, FontStyle::LightItalic, FontStyle::Medium, FontStyle::MediumItalic, FontStyle::Regular, FontStyle::SemiBold, FontStyle::SemiBoldItalic}},
        {Font::OpenSansCondensed, {FontStyle:: Bold, FontStyle::BoldItalic, FontStyle::ExtraBold, FontStyle::ExtraBoldItalic, FontStyle::Italic, FontStyle::Light, FontStyle::LightItalic, FontStyle::Medium, FontStyle::MediumItalic, FontStyle::Regular, FontStyle::SemiBold, FontStyle::SemiBoldItalic}},
        {Font::OpenSansSemiCondensed, {FontStyle:: Bold, FontStyle::BoldItalic, FontStyle::ExtraBold, FontStyle::ExtraBoldItalic, FontStyle::Italic, FontStyle::Light, FontStyle::LightItalic, FontStyle::Medium, FontStyle::MediumItalic, FontStyle::Regular, FontStyle::SemiBold, FontStyle::SemiBoldItalic}},
        {Font::Poppins, {FontStyle::Black, FontStyle::BlackItalic, FontStyle::Bold, FontStyle::BoldItalic, FontStyle::ExtraBold, FontStyle::ExtraBoldItalic, FontStyle::ExtraLight, FontStyle::ExtraLightItalic, FontStyle::Italic, FontStyle::Light, FontStyle::LightItalic, FontStyle::Medium, FontStyle::MediumItalic, FontStyle::Regular, FontStyle::SemiBold, FontStyle::SemiBoldItalic, FontStyle::Thin, FontStyle::ThinItalic}},
        {Font::Roboto, {FontStyle::Black, FontStyle::BlackItalic, FontStyle::Bold, FontStyle::BoldItalic, FontStyle::Italic, FontStyle::Light, FontStyle::LightItalic, FontStyle::Medium, FontStyle::MediumItalic, FontStyle::Regular, FontStyle::Thin, FontStyle::ThinItalic}},
        {Font::Ubuntu, {FontStyle::Bold, FontStyle::BoldItalic, FontStyle::Italic, FontStyle::Light, FontStyle::LightItalic, FontStyle::Medium, FontStyle::MediumItalic, FontStyle::Regular}}
    };
}