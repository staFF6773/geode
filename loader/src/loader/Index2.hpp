#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace geode {
    class IndexItem2 {
    public:
        std::string m_modId;
        VersionInfo m_version;
        std::string m_name;
        std::string m_description;
        std::string m_developer;
        std::string m_downloadUrl;
        bool m_isAPI;

        ModMetadata intoMetadata() const {
            ModMetadata metadata;
            metadata.setID(m_modId);
            metadata.setVersion(m_version);
            metadata.setName(m_name);
            metadata.setDescription(m_description);
            metadata.setDeveloper(m_developer);
            metadata.setIsAPI(m_isAPI);
            return metadata;
        }
    };

    class DetailedIndexItem2 : public IndexItem2 {
    public:
        std::string m_about;
        std::string m_changelog;
        // flattened out dependencies
        // can contain duplicates
        std::vector<IndexItem2> m_dependencies;
    };

    class IndexQuery2 {
        std::string m_search;
    };

    class Index2 {
    public:
        int m_pageLimit = 20;

        static Index2& get() {
            static Index2 instance;
            return instance;
        }

        int getPageLimit() const {
            return m_pageLimit;
        }

        // server callback
        // todo: caching
        void getPageItems(int page, IndexQuery2 const& query, MiniFunction<void(std::vector<IndexItem2> const&)> callback, MiniFunction<void(std::string const&)> error);
    };
};